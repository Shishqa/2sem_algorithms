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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/107/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/107/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/B_river.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/B_river.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/B_river.dir/flags.make

CMakeFiles/B_river.dir/main.cpp.o: CMakeFiles/B_river.dir/flags.make
CMakeFiles/B_river.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/B_river.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/B_river.dir/main.cpp.o -c /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/main.cpp

CMakeFiles/B_river.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/B_river.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/main.cpp > CMakeFiles/B_river.dir/main.cpp.i

CMakeFiles/B_river.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/B_river.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/main.cpp -o CMakeFiles/B_river.dir/main.cpp.s

# Object files for target B_river
B_river_OBJECTS = \
"CMakeFiles/B_river.dir/main.cpp.o"

# External object files for target B_river
B_river_EXTERNAL_OBJECTS =

B_river: CMakeFiles/B_river.dir/main.cpp.o
B_river: CMakeFiles/B_river.dir/build.make
B_river: CMakeFiles/B_river.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable B_river"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/B_river.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/B_river.dir/build: B_river

.PHONY : CMakeFiles/B_river.dir/build

CMakeFiles/B_river.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/B_river.dir/cmake_clean.cmake
.PHONY : CMakeFiles/B_river.dir/clean

CMakeFiles/B_river.dir/depend:
	cd /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug /home/shishqa/Repositories/MIPT/2-semester/Algorithms_Grishutin/03_SearchTrees/B_river/cmake-build-debug/CMakeFiles/B_river.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/B_river.dir/depend

