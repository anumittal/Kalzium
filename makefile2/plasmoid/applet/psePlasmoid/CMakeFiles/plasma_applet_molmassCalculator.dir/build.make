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
include plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/depend.make

# Include the progress variables for this target.
include plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/progress.make

# Include the compile flags for this target's objects.
include plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/flags.make

plasmoid/applet/psePlasmoid/ui_Molmassconfig.h: ../plasmoid/applet/psePlasmoid/Molmassconfig.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_Molmassconfig.h"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/lib/i386-linux-gnu/qt5/bin/uic -o /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid/ui_Molmassconfig.h /home/anu/kalzium/plasmoid/applet/psePlasmoid/Molmassconfig.ui

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/flags.make
plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o: ../plasmoid/applet/psePlasmoid/Molmasscalculator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o -c /home/anu/kalzium/plasmoid/applet/psePlasmoid/Molmasscalculator.cpp

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.i"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anu/kalzium/plasmoid/applet/psePlasmoid/Molmasscalculator.cpp > CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.i

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.s"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anu/kalzium/plasmoid/applet/psePlasmoid/Molmasscalculator.cpp -o CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.s

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.requires:
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.requires

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.provides: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.requires
	$(MAKE) -f plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/build.make plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.provides.build
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.provides

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.provides.build: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/flags.make
plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o: ../plasmoid/applet/psePlasmoid/Periodictable.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/anu/kalzium/makefile2/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o -c /home/anu/kalzium/plasmoid/applet/psePlasmoid/Periodictable.cpp

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.i"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/anu/kalzium/plasmoid/applet/psePlasmoid/Periodictable.cpp > CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.i

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.s"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/anu/kalzium/plasmoid/applet/psePlasmoid/Periodictable.cpp -o CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.s

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.requires:
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.requires

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.provides: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.requires
	$(MAKE) -f plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/build.make plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.provides.build
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.provides

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.provides.build: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o

# Object files for target plasma_applet_molmassCalculator
plasma_applet_molmassCalculator_OBJECTS = \
"CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o" \
"CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o"

# External object files for target plasma_applet_molmassCalculator
plasma_applet_molmassCalculator_EXTERNAL_OBJECTS =

plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/build.make
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: libscience/libscience.so.SOVERSION
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: /usr/lib/i386-linux-gnu/libQt5Xml.so.5.3.0
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: /usr/lib/i386-linux-gnu/libQt5Core.so.5.3.0
plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libplasma_applet_molmassCalculator.so"
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plasma_applet_molmassCalculator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/build: plasmoid/applet/psePlasmoid/libplasma_applet_molmassCalculator.so
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/build

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/requires: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Molmasscalculator.cpp.o.requires
plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/requires: plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/Periodictable.cpp.o.requires
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/requires

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/clean:
	cd /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid && $(CMAKE_COMMAND) -P CMakeFiles/plasma_applet_molmassCalculator.dir/cmake_clean.cmake
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/clean

plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/depend: plasmoid/applet/psePlasmoid/ui_Molmassconfig.h
	cd /home/anu/kalzium/makefile2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anu/kalzium /home/anu/kalzium/plasmoid/applet/psePlasmoid /home/anu/kalzium/makefile2 /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid /home/anu/kalzium/makefile2/plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plasmoid/applet/psePlasmoid/CMakeFiles/plasma_applet_molmassCalculator.dir/depend

