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
CMAKE_SOURCE_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/E_Salesman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/E_Salesman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/E_Salesman.dir/flags.make

CMakeFiles/E_Salesman.dir/main.cpp.o: CMakeFiles/E_Salesman.dir/flags.make
CMakeFiles/E_Salesman.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/E_Salesman.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/E_Salesman.dir/main.cpp.o -c /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/main.cpp

CMakeFiles/E_Salesman.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/E_Salesman.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/main.cpp > CMakeFiles/E_Salesman.dir/main.cpp.i

CMakeFiles/E_Salesman.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/E_Salesman.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/main.cpp -o CMakeFiles/E_Salesman.dir/main.cpp.s

# Object files for target E_Salesman
E_Salesman_OBJECTS = \
"CMakeFiles/E_Salesman.dir/main.cpp.o"

# External object files for target E_Salesman
E_Salesman_EXTERNAL_OBJECTS =

E_Salesman: CMakeFiles/E_Salesman.dir/main.cpp.o
E_Salesman: CMakeFiles/E_Salesman.dir/build.make
E_Salesman: CMakeFiles/E_Salesman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E_Salesman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/E_Salesman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/E_Salesman.dir/build: E_Salesman

.PHONY : CMakeFiles/E_Salesman.dir/build

CMakeFiles/E_Salesman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/E_Salesman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/E_Salesman.dir/clean

CMakeFiles/E_Salesman.dir/depend:
	cd /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug /home/shishqa/repositories/MIPT/2020_2/alg/05_DP/E_Salesman/cmake-build-debug/CMakeFiles/E_Salesman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/E_Salesman.dir/depend

