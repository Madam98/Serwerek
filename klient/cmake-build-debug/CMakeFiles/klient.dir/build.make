# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/oem/Downloads/clion-2021.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/oem/Downloads/clion-2021.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oem/Desktop/Serwerek/klient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oem/Desktop/Serwerek/klient/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/klient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/klient.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/klient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/klient.dir/flags.make

CMakeFiles/klient.dir/client.c.o: CMakeFiles/klient.dir/flags.make
CMakeFiles/klient.dir/client.c.o: ../client.c
CMakeFiles/klient.dir/client.c.o: CMakeFiles/klient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oem/Desktop/Serwerek/klient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/klient.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/klient.dir/client.c.o -MF CMakeFiles/klient.dir/client.c.o.d -o CMakeFiles/klient.dir/client.c.o -c /home/oem/Desktop/Serwerek/klient/client.c

CMakeFiles/klient.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/klient.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/oem/Desktop/Serwerek/klient/client.c > CMakeFiles/klient.dir/client.c.i

CMakeFiles/klient.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/klient.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/oem/Desktop/Serwerek/klient/client.c -o CMakeFiles/klient.dir/client.c.s

# Object files for target klient
klient_OBJECTS = \
"CMakeFiles/klient.dir/client.c.o"

# External object files for target klient
klient_EXTERNAL_OBJECTS =

klient: CMakeFiles/klient.dir/client.c.o
klient: CMakeFiles/klient.dir/build.make
klient: CMakeFiles/klient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oem/Desktop/Serwerek/klient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable klient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/klient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/klient.dir/build: klient
.PHONY : CMakeFiles/klient.dir/build

CMakeFiles/klient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/klient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/klient.dir/clean

CMakeFiles/klient.dir/depend:
	cd /home/oem/Desktop/Serwerek/klient/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oem/Desktop/Serwerek/klient /home/oem/Desktop/Serwerek/klient /home/oem/Desktop/Serwerek/klient/cmake-build-debug /home/oem/Desktop/Serwerek/klient/cmake-build-debug /home/oem/Desktop/Serwerek/klient/cmake-build-debug/CMakeFiles/klient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/klient.dir/depend

