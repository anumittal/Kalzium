# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anu/kalzium

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anu/kalzium/makefile2

# Include any dependencies generated for this target.
include plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/depend.make

# Include the progress variables for this target.
include plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/progress.make

# Include the compile flags for this target's objects.
include plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/flags.make

plasmoid/applet/nuclearPlasmoid/ui_nuclearCalculatorConfig.h: ../plasmoid/applet/nuclearPlasmoid/nuclearCalculatorConfig.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_nuclearCalculatorConfig.h"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/lib/i386-linux-gnu/qt5/bin/uic -o /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid/ui_nuclearCalculatorConfig.h /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/nuclearCalculatorConfig.ui

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/flags.make
plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o: ../plasmoid/applet/nuclearPlasmoid/nuclearCalculator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o -c /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/nuclearCalculator.cpp

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.i"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/nuclearCalculator.cpp > CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.i

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.s"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/nuclearCalculator.cpp -o CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.s

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.requires:
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.requires

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.provides: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.requires
	$(MAKE) -f plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/build.make plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.provides.build
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.provides

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.provides.build: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/flags.make
plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o: ../plasmoid/applet/nuclearPlasmoid/kalziumdataobject.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o -c /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/kalziumdataobject.cpp

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.i"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/kalziumdataobject.cpp > CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.i

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.s"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid/kalziumdataobject.cpp -o CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.s

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.requires:
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.requires

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.provides: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.requires
	$(MAKE) -f plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/build.make plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.provides.build
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.provides

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.provides.build: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o

# Object files for target nuclearCalculator
nuclearCalculator_OBJECTS = \
"CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o" \
"CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o"

# External object files for target nuclearCalculator
nuclearCalculator_EXTERNAL_OBJECTS =

plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/build.make
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: libscience/libscience.so.SOVERSION
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: /usr/lib/i386-linux-gnu/libQt5Xml.so.5.3.0
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: /usr/lib/i386-linux-gnu/libQt5Core.so.5.3.0
plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libnuclearCalculator.so"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nuclearCalculator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/build: plasmoid/applet/nuclearPlasmoid/libnuclearCalculator.so
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/build

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/requires: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/nuclearCalculator.cpp.o.requires
plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/requires: plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/kalziumdataobject.cpp.o.requires
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/requires

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/clean:
	cd /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid && $(CMAKE_COMMAND) -P CMakeFiles/nuclearCalculator.dir/cmake_clean.cmake
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/clean

plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/depend: plasmoid/applet/nuclearPlasmoid/ui_nuclearCalculatorConfig.h
	cd /home/anu/kalzium/makefile2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anu/kalzium /home/anu/kalzium/plasmoid/applet/nuclearPlasmoid /home/anu/kalzium/makefile2 /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid /home/anu/kalzium/makefile2/plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plasmoid/applet/nuclearPlasmoid/CMakeFiles/nuclearCalculator.dir/depend

