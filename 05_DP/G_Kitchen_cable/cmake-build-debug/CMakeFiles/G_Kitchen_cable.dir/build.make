# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/111/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/111/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/G_Kitchen_cable.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/G_Kitchen_cable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/G_Kitchen_cable.dir/flags.make

CMakeFiles/G_Kitchen_cable.dir/main.cpp.o: CMakeFiles/G_Kitchen_cable.dir/flags.make
CMakeFiles/G_Kitchen_cable.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/G_Kitchen_cable.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/G_Kitchen_cable.dir/main.cpp.o -c /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/main.cpp

CMakeFiles/G_Kitchen_cable.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/G_Kitchen_cable.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/main.cpp > CMakeFiles/G_Kitchen_cable.dir/main.cpp.i

CMakeFiles/G_Kitchen_cable.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/G_Kitchen_cable.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/main.cpp -o CMakeFiles/G_Kitchen_cable.dir/main.cpp.s

# Object files for target G_Kitchen_cable
G_Kitchen_cable_OBJECTS = \
"CMakeFiles/G_Kitchen_cable.dir/main.cpp.o"

# External object files for target G_Kitchen_cable
G_Kitchen_cable_EXTERNAL_OBJECTS =

G_Kitchen_cable: CMakeFiles/G_Kitchen_cable.dir/main.cpp.o
G_Kitchen_cable: CMakeFiles/G_Kitchen_cable.dir/build.make
G_Kitchen_cable: CMakeFiles/G_Kitchen_cable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable G_Kitchen_cable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/G_Kitchen_cable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/G_Kitchen_cable.dir/build: G_Kitchen_cable

.PHONY : CMakeFiles/G_Kitchen_cable.dir/build

CMakeFiles/G_Kitchen_cable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/G_Kitchen_cable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/G_Kitchen_cable.dir/clean

CMakeFiles/G_Kitchen_cable.dir/depend:
	cd /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/G_Kitchen_cable/cmake-build-debug/CMakeFiles/G_Kitchen_cable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/G_Kitchen_cable.dir/depend

