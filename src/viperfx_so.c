#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include "viperfx_so.h"

#define ViPERFX_SO "libviperfx.so"
#define ViPERFX_ENTRYPOINT "viperfx_create_instance"

void* viperfx_load_library (const char * so_path_name)
{
  if (so_path_name == NULL) {
    return dlopen (ViPERFX_SO, RTLD_NOW);
  } else {
    return dlopen (so_path_name, RTLD_NOW);
  }
}

void viperfx_unload_library (void * handle)
{
  if (handle == NULL)
    return;
  dlclose (handle);
}

fn_viperfx_ep query_viperfx_entrypoint (void * handle)
{
  if (handle == NULL)
    return NULL;
  return (fn_viperfx_ep)dlsym (
      handle, ViPERFX_ENTRYPOINT);
}

int viperfx_command_set_px4_vx4x1 (viperfx_interface * intf,
	int32_t param, int32_t value)
{
  int32_t cmd_data[3];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 1;
  cmd_data[2] = value;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_px4_vx4x2 (viperfx_interface * intf,
	int32_t param, int32_t value_l, int32_t value_h)
{
  int32_t cmd_data[4];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 2;
  cmd_data[2] = value_l;
  cmd_data[3] = value_h;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_px4_vx4x3 (viperfx_interface * intf,
	int32_t param, int32_t value_l, int32_t value_h, int32_t value_e)
{
  int32_t cmd_data[5];
  cmd_data[0] = param;
  cmd_data[1] = sizeof(int32_t) * 3;
  cmd_data[2] = value_l;
  cmd_data[3] = value_h;
  cmd_data[4] = value_e;

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
    return FALSE;
  }
  return TRUE;
}

int viperfx_command_set_px4_vx1x1024 (viperfx_interface * intf,
                                   int32_t param, const char *floatData)
{

    //----- This section is WIP -----
    if(strlen(floatData) < 1){
        printf("floatData < 1\n"); //Debug message
        return FALSE;
    }
    char input[strlen(floatData)];
    strncpy(input,floatData,strlen(floatData));

    char *token = strtok(input, ";");

    double size=strtod(token,NULL);
    printf("%.15f:", size);
    double signal[25];
    signal[0] = size;
    int i=0;
    unsigned char* bAry = calloc(1024,1);

    while (token != NULL) //Split the string into an array
    {
        printf("%s\n", token);
        token = strtok(NULL, ";");
        if(token !=NULL){
            i=i+1;
            double tmp = strtod(token,NULL);
            signal[i] = tmp;
            printf("%.15f:",signal[i]);

        }
    }
    int length = i;
    printf("Length: %u (%u)\n",length,length*(sizeof(double)));
    memcpy(bAry, signal, length*(sizeof(double)));
    for (i=0; i<length*(sizeof(double)); i++){
        printf("%u,",bAry[i]);
    }
    //---------------------------

    char cmd_data[4 + 1024];
    int32_t * cmd_data_int = (int32_t *)cmd_data;

    if (sizeof(signal) >= 1024)
        return FALSE;

    memset (cmd_data, 0, sizeof(cmd_data));
    cmd_data_int[0] = PARAM_HPFX_VDDC_COEFFS;
    cmd_data_int[1] = 1024;
    cmd_data_int[2] = (int32_t)sizeof(bAry);
    memcpy (&cmd_data_int[3],
            bAry, sizeof(bAry));

    if (intf->command (intf, COMMAND_CODE_SET,
                    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
     return FALSE;
 }
    return TRUE;
}
int viperfx_command_set_px4_vx1x256 (viperfx_interface * intf,int32_t param,
                                 const char * str)
{
    char cmd_data[4 + 256];
    int32_t * cmd_data_int = (int32_t *)cmd_data;

    if (strlen (str) >= 256)
        return FALSE;

    memset (cmd_data, 0, sizeof(cmd_data));
    cmd_data_int[0] = param;
    cmd_data_int[1] = 256;
    cmd_data_int[2] = (int32_t)strlen (str);
    memcpy (&cmd_data_int[3],
            str, strlen (str));

    if (intf->command (intf, COMMAND_CODE_SET,
                       sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
        return FALSE;
    }
    return TRUE;
}


int viperfx_command_set_ir_path (viperfx_interface * intf,
    const char * pathname)
{
  char cmd_data[4 + 256];
  int32_t * cmd_data_int = (int32_t *)cmd_data;

  if (strlen (pathname) >= 256)
    return FALSE;

  memset (cmd_data, 0, sizeof(cmd_data));
  cmd_data_int[0] = PARAM_HPFX_CONV_UPDATEKERNEL;
  cmd_data_int[1] = 256;
  cmd_data_int[2] = (int32_t)strlen (pathname);
  memcpy (&cmd_data_int[3],
      pathname, strlen (pathname));

  if (intf->command (intf, COMMAND_CODE_SET,
    sizeof(cmd_data), cmd_data, NULL, NULL) != 0) {
      return FALSE;
  }
  return TRUE;
}

