# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/phagmaier/Desktop/Code/2048

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phagmaier/Desktop/Code/2048/bin

# Include any dependencies generated for this target.
include CMakeFiles/runme.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/runme.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/runme.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/runme.dir/flags.make

CMakeFiles/runme.dir/brain.cpp.o: CMakeFiles/runme.dir/flags.make
CMakeFiles/runme.dir/brain.cpp.o: /home/phagmaier/Desktop/Code/2048/brain.cpp
CMakeFiles/runme.dir/brain.cpp.o: CMakeFiles/runme.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/phagmaier/Desktop/Code/2048/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/runme.dir/brain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/runme.dir/brain.cpp.o -MF CMakeFiles/runme.dir/brain.cpp.o.d -o CMakeFiles/runme.dir/brain.cpp.o -c /home/phagmaier/Desktop/Code/2048/brain.cpp

CMakeFiles/runme.dir/brain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/runme.dir/brain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phagmaier/Desktop/Code/2048/brain.cpp > CMakeFiles/runme.dir/brain.cpp.i

CMakeFiles/runme.dir/brain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/runme.dir/brain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phagmaier/Desktop/Code/2048/brain.cpp -o CMakeFiles/runme.dir/brain.cpp.s

CMakeFiles/runme.dir/main.cpp.o: CMakeFiles/runme.dir/flags.make
CMakeFiles/runme.dir/main.cpp.o: /home/phagmaier/Desktop/Code/2048/main.cpp
CMakeFiles/runme.dir/main.cpp.o: CMakeFiles/runme.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/phagmaier/Desktop/Code/2048/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/runme.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/runme.dir/main.cpp.o -MF CMakeFiles/runme.dir/main.cpp.o.d -o CMakeFiles/runme.dir/main.cpp.o -c /home/phagmaier/Desktop/Code/2048/main.cpp

CMakeFiles/runme.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/runme.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phagmaier/Desktop/Code/2048/main.cpp > CMakeFiles/runme.dir/main.cpp.i

CMakeFiles/runme.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/runme.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phagmaier/Desktop/Code/2048/main.cpp -o CMakeFiles/runme.dir/main.cpp.s

# Object files for target runme
runme_OBJECTS = \
"CMakeFiles/runme.dir/brain.cpp.o" \
"CMakeFiles/runme.dir/main.cpp.o"

# External object files for target runme
runme_EXTERNAL_OBJECTS =

runme: CMakeFiles/runme.dir/brain.cpp.o
runme: CMakeFiles/runme.dir/main.cpp.o
runme: CMakeFiles/runme.dir/build.make
runme: CMakeFiles/runme.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/phagmaier/Desktop/Code/2048/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable runme"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runme.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/runme.dir/build: runme
.PHONY : CMakeFiles/runme.dir/build

CMakeFiles/runme.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/runme.dir/cmake_clean.cmake
.PHONY : CMakeFiles/runme.dir/clean

CMakeFiles/runme.dir/depend:
	cd /home/phagmaier/Desktop/Code/2048/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phagmaier/Desktop/Code/2048 /home/phagmaier/Desktop/Code/2048 /home/phagmaier/Desktop/Code/2048/bin /home/phagmaier/Desktop/Code/2048/bin /home/phagmaier/Desktop/Code/2048/bin/CMakeFiles/runme.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/runme.dir/depend

