# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\Client\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WinSock.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WinSock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WinSock.dir/flags.make

CMakeFiles/WinSock.dir/client.c.obj: CMakeFiles/WinSock.dir/flags.make
CMakeFiles/WinSock.dir/client.c.obj: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/WinSock.dir/client.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\WinSock.dir\client.c.obj   -c F:\Client\client.c

CMakeFiles/WinSock.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WinSock.dir/client.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E F:\Client\client.c > CMakeFiles\WinSock.dir\client.c.i

CMakeFiles/WinSock.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WinSock.dir/client.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S F:\Client\client.c -o CMakeFiles\WinSock.dir\client.c.s

CMakeFiles/WinSock.dir/client.c.obj.requires:

.PHONY : CMakeFiles/WinSock.dir/client.c.obj.requires

CMakeFiles/WinSock.dir/client.c.obj.provides: CMakeFiles/WinSock.dir/client.c.obj.requires
	$(MAKE) -f CMakeFiles\WinSock.dir\build.make CMakeFiles/WinSock.dir/client.c.obj.provides.build
.PHONY : CMakeFiles/WinSock.dir/client.c.obj.provides

CMakeFiles/WinSock.dir/client.c.obj.provides.build: CMakeFiles/WinSock.dir/client.c.obj


# Object files for target WinSock
WinSock_OBJECTS = \
"CMakeFiles/WinSock.dir/client.c.obj"

# External object files for target WinSock
WinSock_EXTERNAL_OBJECTS =

WinSock.exe: CMakeFiles/WinSock.dir/client.c.obj
WinSock.exe: CMakeFiles/WinSock.dir/build.make
WinSock.exe: CMakeFiles/WinSock.dir/linklibs.rsp
WinSock.exe: CMakeFiles/WinSock.dir/objects1.rsp
WinSock.exe: CMakeFiles/WinSock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\Client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable WinSock.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\WinSock.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WinSock.dir/build: WinSock.exe

.PHONY : CMakeFiles/WinSock.dir/build

CMakeFiles/WinSock.dir/requires: CMakeFiles/WinSock.dir/client.c.obj.requires

.PHONY : CMakeFiles/WinSock.dir/requires

CMakeFiles/WinSock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\WinSock.dir\cmake_clean.cmake
.PHONY : CMakeFiles/WinSock.dir/clean

CMakeFiles/WinSock.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\Client F:\Client F:\Client\cmake-build-debug F:\Client\cmake-build-debug F:\Client\cmake-build-debug\CMakeFiles\WinSock.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WinSock.dir/depend
