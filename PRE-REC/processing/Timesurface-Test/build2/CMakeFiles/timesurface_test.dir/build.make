# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2

# Include any dependencies generated for this target.
include CMakeFiles/timesurface_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/timesurface_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/timesurface_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/timesurface_test.dir/flags.make

CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o: CMakeFiles/timesurface_test.dir/flags.make
CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o: ../timesurface_test.cpp
CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o: CMakeFiles/timesurface_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o -MF CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o.d -o CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o -c /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/timesurface_test.cpp

CMakeFiles/timesurface_test.dir/timesurface_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timesurface_test.dir/timesurface_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/timesurface_test.cpp > CMakeFiles/timesurface_test.dir/timesurface_test.cpp.i

CMakeFiles/timesurface_test.dir/timesurface_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timesurface_test.dir/timesurface_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/timesurface_test.cpp -o CMakeFiles/timesurface_test.dir/timesurface_test.cpp.s

# Object files for target timesurface_test
timesurface_test_OBJECTS = \
"CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o"

# External object files for target timesurface_test
timesurface_test_EXTERNAL_OBJECTS =

timesurface_test: CMakeFiles/timesurface_test.dir/timesurface_test.cpp.o
timesurface_test: CMakeFiles/timesurface_test.dir/build.make
timesurface_test: libtsLib.a
timesurface_test: /usr/lib/libmetavision_sdk_driver.so.3.0.1
timesurface_test: /usr/lib/libmetavision_sdk_core.so.3.0.1
timesurface_test: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.4.5.4d
timesurface_test: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.4.5.4d
timesurface_test: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.4.5.4d
timesurface_test: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.4.5.4d
timesurface_test: /usr/lib/x86_64-linux-gnu/libopencv_core.so.4.5.4d
timesurface_test: /usr/lib/x86_64-linux-gnu/libboost_timer.so.1.74.0
timesurface_test: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.74.0
timesurface_test: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
timesurface_test: /usr/lib/libmetavision_hal_discovery.so.3.0.1
timesurface_test: /usr/lib/libmetavision_hal.so.3.0.1
timesurface_test: /usr/lib/libmetavision_sdk_base.so.3.0.1
timesurface_test: CMakeFiles/timesurface_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable timesurface_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timesurface_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/timesurface_test.dir/build: timesurface_test
.PHONY : CMakeFiles/timesurface_test.dir/build

CMakeFiles/timesurface_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/timesurface_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/timesurface_test.dir/clean

CMakeFiles/timesurface_test.dir/depend:
	cd /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2 /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2 /media/jmwul/31d3e938-8db0-4b28-a7bc-efc206c69ad1/home/theia-experiments/PRE-REC/processing/Timesurface-Test/build2/CMakeFiles/timesurface_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/timesurface_test.dir/depend
