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
CMAKE_SOURCE_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/F_nails.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/F_nails.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/F_nails.dir/flags.make

CMakeFiles/F_nails.dir/main.cpp.o: CMakeFiles/F_nails.dir/flags.make
CMakeFiles/F_nails.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/F_nails.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/F_nails.dir/main.cpp.o -c /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/main.cpp

CMakeFiles/F_nails.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/F_nails.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/main.cpp > CMakeFiles/F_nails.dir/main.cpp.i

CMakeFiles/F_nails.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/F_nails.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/main.cpp -o CMakeFiles/F_nails.dir/main.cpp.s

# Object files for target F_nails
F_nails_OBJECTS = \
"CMakeFiles/F_nails.dir/main.cpp.o"

# External object files for target F_nails
F_nails_EXTERNAL_OBJECTS =

F_nails: CMakeFiles/F_nails.dir/main.cpp.o
F_nails: CMakeFiles/F_nails.dir/build.make
F_nails: CMakeFiles/F_nails.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable F_nails"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/F_nails.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/F_nails.dir/build: F_nails

.PHONY : CMakeFiles/F_nails.dir/build

CMakeFiles/F_nails.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/F_nails.dir/cmake_clean.cmake
.PHONY : CMakeFiles/F_nails.dir/clean

CMakeFiles/F_nails.dir/depend:
	cd /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/F_nails/cmake-build-debug/CMakeFiles/F_nails.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/F_nails.dir/depend

