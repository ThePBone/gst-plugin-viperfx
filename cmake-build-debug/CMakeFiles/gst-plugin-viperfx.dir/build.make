# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/tim/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.103/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/tim/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.103/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tim/Development/gst-plugin-viperfx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tim/Development/gst-plugin-viperfx/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gst-plugin-viperfx.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gst-plugin-viperfx.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gst-plugin-viperfx.dir/flags.make

CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o: CMakeFiles/gst-plugin-viperfx.dir/flags.make
CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o: ../src/gstviperfx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tim/Development/gst-plugin-viperfx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o   -c /home/tim/Development/gst-plugin-viperfx/src/gstviperfx.c

CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tim/Development/gst-plugin-viperfx/src/gstviperfx.c > CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.i

CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tim/Development/gst-plugin-viperfx/src/gstviperfx.c -o CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.s

CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o: CMakeFiles/gst-plugin-viperfx.dir/flags.make
CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o: ../src/viperfx_so.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tim/Development/gst-plugin-viperfx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o   -c /home/tim/Development/gst-plugin-viperfx/src/viperfx_so.c

CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tim/Development/gst-plugin-viperfx/src/viperfx_so.c > CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.i

CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tim/Development/gst-plugin-viperfx/src/viperfx_so.c -o CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.s

# Object files for target gst-plugin-viperfx
gst__plugin__viperfx_OBJECTS = \
"CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o" \
"CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o"

# External object files for target gst-plugin-viperfx
gst__plugin__viperfx_EXTERNAL_OBJECTS =

libgst-plugin-viperfx.so: CMakeFiles/gst-plugin-viperfx.dir/src/gstviperfx.c.o
libgst-plugin-viperfx.so: CMakeFiles/gst-plugin-viperfx.dir/src/viperfx_so.c.o
libgst-plugin-viperfx.so: CMakeFiles/gst-plugin-viperfx.dir/build.make
libgst-plugin-viperfx.so: CMakeFiles/gst-plugin-viperfx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tim/Development/gst-plugin-viperfx/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library libgst-plugin-viperfx.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gst-plugin-viperfx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gst-plugin-viperfx.dir/build: libgst-plugin-viperfx.so

.PHONY : CMakeFiles/gst-plugin-viperfx.dir/build

CMakeFiles/gst-plugin-viperfx.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gst-plugin-viperfx.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gst-plugin-viperfx.dir/clean

CMakeFiles/gst-plugin-viperfx.dir/depend:
	cd /home/tim/Development/gst-plugin-viperfx/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tim/Development/gst-plugin-viperfx /home/tim/Development/gst-plugin-viperfx /home/tim/Development/gst-plugin-viperfx/cmake-build-debug /home/tim/Development/gst-plugin-viperfx/cmake-build-debug /home/tim/Development/gst-plugin-viperfx/cmake-build-debug/CMakeFiles/gst-plugin-viperfx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gst-plugin-viperfx.dir/depend

