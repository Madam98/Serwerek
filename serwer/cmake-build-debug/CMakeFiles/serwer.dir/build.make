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
CMAKE_COMMAND = /home/adam/Pulpit/clion-2021.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/adam/Pulpit/clion-2021.3.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adam/Pulpit/Serwerek/serwer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adam/Pulpit/Serwerek/serwer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/serwer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/serwer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/serwer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serwer.dir/flags.make

CMakeFiles/serwer.dir/main.c.o: CMakeFiles/serwer.dir/flags.make
CMakeFiles/serwer.dir/main.c.o: ../main.c
CMakeFiles/serwer.dir/main.c.o: CMakeFiles/serwer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adam/Pulpit/Serwerek/serwer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/serwer.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/serwer.dir/main.c.o -MF CMakeFiles/serwer.dir/main.c.o.d -o CMakeFiles/serwer.dir/main.c.o -c /home/adam/Pulpit/Serwerek/serwer/main.c

CMakeFiles/serwer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serwer.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adam/Pulpit/Serwerek/serwer/main.c > CMakeFiles/serwer.dir/main.c.i

CMakeFiles/serwer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serwer.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adam/Pulpit/Serwerek/serwer/main.c -o CMakeFiles/serwer.dir/main.c.s

# Object files for target serwer
serwer_OBJECTS = \
"CMakeFiles/serwer.dir/main.c.o"

# External object files for target serwer
serwer_EXTERNAL_OBJECTS =

serwer: CMakeFiles/serwer.dir/main.c.o
serwer: CMakeFiles/serwer.dir/build.make
serwer: CMakeFiles/serwer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adam/Pulpit/Serwerek/serwer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable serwer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serwer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serwer.dir/build: serwer
.PHONY : CMakeFiles/serwer.dir/build

CMakeFiles/serwer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serwer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serwer.dir/clean

CMakeFiles/serwer.dir/depend:
	cd /home/adam/Pulpit/Serwerek/serwer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adam/Pulpit/Serwerek/serwer /home/adam/Pulpit/Serwerek/serwer /home/adam/Pulpit/Serwerek/serwer/cmake-build-debug /home/adam/Pulpit/Serwerek/serwer/cmake-build-debug /home/adam/Pulpit/Serwerek/serwer/cmake-build-debug/CMakeFiles/serwer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serwer.dir/depend

