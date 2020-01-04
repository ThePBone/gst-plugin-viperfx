/*
    autoreload.h
    Copyright (C) 2019 ThePBone <tim.schneeberger(at)outlook.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GST_PLUGIN_VIPERFX_FILEWATCHER_H
#define GST_PLUGIN_VIPERFX_FILEWATCHER_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <stdbool.h>
#include "gstviperfx.h"

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

bool reloadRequired = FALSE;
pthread_mutex_t lock;
pthread_t th1;

/// [Thread] File watcher service
/// Sets reloadRequired to 1 if audio.conf has been modified.
void* DoFileCheck(void* args){
    int length;
    int fd;
    int wd;
    char *wdir = (char*)args;
    char buffer[BUF_LEN];

    fd = inotify_init();

    if ( fd < 0 ) {
        perror( "inotify_init" );
    }

    printf("[I] Autoreload: inotify watch added to %s\n",wdir);
    wd = inotify_add_watch( fd, wdir,
                            IN_MODIFY | IN_CREATE );

    while (TRUE) {
        int i = 0;
        length = read( fd, buffer, BUF_LEN );

        if ( length < 0 ) {
            perror( "read" );
        }

        while ( i < length ) {
            struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
            if ( event->len ) {
                if( (event->mask & IN_CREATE || event->mask & IN_MODIFY) && !(event->mask & IN_ISDIR) ){
                    if(strcmp(event->name,"audio.conf")==0) {
                        pthread_mutex_lock(&lock);
                        reloadRequired = 1;
                        pthread_mutex_unlock(&lock);
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }
    ( void ) inotify_rm_watch( fd, wd );
    ( void ) close( fd );
    return NULL;
}

///Initialize inotify file-watcher service
void InitFWatch(Gstviperfx* self){
    printf("[I] Autoreload initializing...\n");
    if(!*self->workdir){
        printf("[W] Autoreload disabled: path to configuration directory is not set (NULL)\n");
        return;
    }
    int p = 0;
    for (int i = 0; i < strlen(self->workdir); ++i) {
        p |= self->workdir[i];
    }
    if (p == 0) {
        printf("[W] Autoreload disabled: path to configuration directory is not set (zero data)\n");
        return;
    }
    pthread_mutex_init(&lock,NULL);
    pthread_create(&th1, NULL, &DoFileCheck,self->workdir);
}

///Parse value of specified key and load it into memory
void ParseLine(char* input,char* value,Gstviperfx* self){
    if( strcmp(input,"fx_enable")==0 )self->fx_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"agc_enable")==0 ) self->agc_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"agc_maxgain")==0 ) self->agc_maxgain = atoi(value);
    else if( strcmp(input,"agc_ratio")==0 ) self->agc_ratio = atoi(value);
    else if( strcmp(input,"agc_volume")==0 ) self->agc_volume = atoi(value);
    else if( strcmp(input,"ax_enable")==0 ) self->ax_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"ax_mode")==0 ) self->ax_mode = atoi(value);
    else if( strcmp(input,"colm_enable")==0 ) self->colm_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"colm_depth")==0 ) self->colm_depth = atoi(value);
    else if( strcmp(input,"colm_midimage")==0 ) self->colm_midimage = atoi(value);
    else if( strcmp(input,"colm_widening")==0 ) self->colm_widening = atoi(value);
    else if( strcmp(input,"conv_enable")==0 ) self->conv_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"conv_cc_level")==0 ) self->conv_cc_level = atoi(value);
    else if( strcmp(input,"conv_ir_path")==0 ){
        //Not implemented...
        //Some audio.conf files use shell expressions inside the conv_ir_path property
        //Since we cannot evaluate these expressions here, we need to do a full reload
    }
    else if( strcmp(input,"cure_enable")==0 ) self->cure_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"cure_level")==0 ) self->cure_level = atoi(value);
    else if( strcmp(input,"ds_enable")==0 ) self->ds_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"ds_level")==0 ) self->ds_level = atoi(value);
    else if( strcmp(input,"dynsys_enable")==0 ) self->dynsys_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"dynsys_bassgain")==0 ) self->dynsys_bassgain = atoi(value);
    else if( strcmp(input,"dynsys_xcoeff1")==0 ) self->dynsys_xcoeffs = atoi(value);
    else if( strcmp(input,"dynsys_xcoeff2")==0 ) self->dynsys_xcoeffs2 = atoi(value);
    else if( strcmp(input,"dynsys_ycoeff1")==0 ) self->dynsys_ycoeffs = atoi(value);
    else if( strcmp(input,"dynsys_ycoeff2")==0 ) self->dynsys_ycoeffs2 = atoi(value);
    else if( strcmp(input,"dynsys_sidegain1")==0 ) self->dynsys_sidegain = atoi(value);
    else if( strcmp(input,"dynsys_sidegain2")==0 ) self->dynsys_sidegain2 = atoi(value);
    else if( strcmp(input,"eq_enable")==0 ) self->eq_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"eq_band1")==0 ) self->eq_band_level[0] = atoi(value);
    else if( strcmp(input,"eq_band2")==0 ) self->eq_band_level[1] = atoi(value);
    else if( strcmp(input,"eq_band3")==0 ) self->eq_band_level[2] = atoi(value);
    else if( strcmp(input,"eq_band4")==0 ) self->eq_band_level[3] = atoi(value);
    else if( strcmp(input,"eq_band5")==0 ) self->eq_band_level[4] = atoi(value);
    else if( strcmp(input,"eq_band6")==0 ) self->eq_band_level[5] = atoi(value);
    else if( strcmp(input,"eq_band7")==0 ) self->eq_band_level[6] = atoi(value);
    else if( strcmp(input,"eq_band8")==0 ) self->eq_band_level[7] = atoi(value);
    else if( strcmp(input,"eq_band9")==0 ) self->eq_band_level[8] = atoi(value);
    else if( strcmp(input,"eq_band10")==0 ) self->eq_band_level[9] = atoi(value);
    else if( strcmp(input,"fetcomp_enable")==0 ) self->fetcomp_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"fetcomp_attack")==0 ) self->fetcomp_attack = atoi(value);
    else if( strcmp(input,"fetcomp_gain")==0 ) self->fetcomp_gain = atoi(value);
    else if( strcmp(input,"fetcomp_release")==0 ) self->fetcomp_release = atoi(value);
    else if( strcmp(input,"fetcomp_threshold")==0 ) self->fetcomp_threshold = atoi(value);
    else if( strcmp(input,"fetcomp_ratio")==0 ) self->fetcomp_ratio = atoi(value);
    else if( strcmp(input,"fetcomp_kneewidth")==0 ) self->fetcomp_kneewidth = atoi(value);
    else if( strcmp(input,"fetcomp_meta_adapt")==0 ) self->fetcomp_meta_adapt = atoi(value);
    else if( strcmp(input,"fetcomp_meta_crest")==0 ) self->fetcomp_meta_crest = atoi(value);
    else if( strcmp(input,"fetcomp_meta_kneemulti")==0 ) self->fetcomp_meta_kneemulti = atoi(value);
    else if( strcmp(input,"fetcomp_meta_maxattack")==0 ) self->fetcomp_meta_maxattack = atoi(value);
    else if( strcmp(input,"fetcomp_meta_maxrelease")==0 ) self->fetcomp_meta_maxrelease = atoi(value);
    else if( strcmp(input,"fetcomp_noclip")==0 ) self->fetcomp_noclip = strcmp(value, "true") == 0;
    else if( strcmp(input,"fetcomp_autoattack")==0 ) self->fetcomp_autoattack = strcmp(value, "true") == 0;
    else if( strcmp(input,"fetcomp_autogain")==0 ) self->fetcomp_autogain = strcmp(value, "true") == 0;
    else if( strcmp(input,"fetcomp_autoknee")==0 ) self->fetcomp_autoknee = strcmp(value, "true") == 0;
    else if( strcmp(input,"fetcomp_autorelease")==0 ) self->fetcomp_autorelease = strcmp(value, "true") == 0;
    else if( strcmp(input,"lim_threshold")==0 ) self->lim_threshold = atoi(value);
    else if( strcmp(input,"out_pan")==0 ) self->out_pan = atoi(value);
    else if( strcmp(input,"out_volume")==0 ) self->out_volume = atoi(value);
    else if( strcmp(input,"reverb_enable")==0 ) self->reverb_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"reverb_damp")==0 ) self->reverb_damp = atoi(value);
    else if( strcmp(input,"reverb_dry")==0 ) self->reverb_dry = atoi(value);
    else if( strcmp(input,"reverb_roomsize")==0 ) self->reverb_roomsize = atoi(value);
    else if( strcmp(input,"reverb_wet")==0 ) self->reverb_wet = atoi(value);
    else if( strcmp(input,"reverb_width")==0 ) self->reverb_width = atoi(value);
    else if( strcmp(input,"tube_enable")==0 ) self->tube_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"vb_enable")==0 ) self->vb_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"vb_freq")==0 ) self->vb_freq = atoi(value);
    else if( strcmp(input,"vb_gain")==0 ) self->vb_gain = atoi(value);
    else if( strcmp(input,"vb_mode")==0 ) self->vb_mode = atoi(value);
    else if( strcmp(input,"vc_enable")==0 ) self->vc_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"vc_level")==0 ) self->vc_level = atoi(value);
    else if( strcmp(input,"vc_mode")==0 ) self->vc_mode = atoi(value);
    else if( strcmp(input,"vhe_enable")==0 ) self->vhe_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"vhe_level")==0 ) self->vhe_level = atoi(value);
    else if( strcmp(input,"vse_enable")==0 ) self->vse_enabled = strcmp(value, "true") == 0;
    else if( strcmp(input,"vse_bark_cons")==0 ) self->vse_bark_cons = atoi(value);
    else if( strcmp(input,"vse_ref_bark")==0 ) self->vse_ref_bark = atoi(value);
}

///Read configuration, iterate through each line and load it into memory
void ParseConfiguration(char* dirpath,Gstviperfx* self){
    char* fullpath = (char*)malloc(strlen(dirpath)+50);
    memset (fullpath, 0, sizeof(strlen(dirpath)+50));
    strcpy(fullpath,dirpath);
    strcat(fullpath,"/audio.conf");
    pthread_mutex_lock(&lock);

    char *name = (char*)calloc(128,1);
    char *val = (char*)calloc(4096,1);
    FILE *file = fopen(fullpath, "r");
    if(file==NULL)
    {
        pthread_mutex_unlock(&lock);
        printf("[E] Autoreload: Unable to open audio.conf at %s\n",fullpath);
        return;
    }
    while (fscanf(file, "%127[^=]=%4095[^\n]%*c", name, val) == 2)
        ParseLine(name,val,self);

    free(name);
    free(val);
    free(fullpath);
    fclose(file);
    pthread_mutex_unlock(&lock);
}

///Check if a reload has been issued by the file-watcher. If yes, we will update all parameters
int SynchronizeConfig(Gstviperfx* self){
    if(reloadRequired == 1){

        viperfx_command_get_px4_vx4x1(self->vfx,0x08009);

        g_mutex_lock(&self->lock);
        ParseConfiguration(self->workdir,self);
        g_mutex_unlock(&self->lock);

        pthread_mutex_lock(&lock);
        reloadRequired = 0;
        pthread_mutex_unlock(&lock);
        return 1;
    }
    return 0;
}

#endif //GST_PLUGIN_VIPERFX_FILEWATCHER_H
