# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tony/esp/IOMTV4_power

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tony/esp/IOMTV4_power/build

# Utility rule file for erase_flash.

# Include the progress variables for this target.
include CMakeFiles/erase_flash.dir/progress.make

CMakeFiles/erase_flash:
	cd /home/tony/esp/esp-idf/components/esptool_py && /usr/local/bin/cmake -D IDF_PATH="/home/tony/esp/esp-idf" -D SERIAL_TOOL="/home/tony/.espressif/python_env/idf4.3_py3.9_env/bin/python /home/tony/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32s2" -D SERIAL_TOOL_ARGS="erase_flash" -P run_serial_tool.cmake

erase_flash: CMakeFiles/erase_flash
erase_flash: CMakeFiles/erase_flash.dir/build.make

.PHONY : erase_flash

# Rule to build all files generated by this target.
CMakeFiles/erase_flash.dir/build: erase_flash

.PHONY : CMakeFiles/erase_flash.dir/build

CMakeFiles/erase_flash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/erase_flash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/erase_flash.dir/clean

CMakeFiles/erase_flash.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/IOMTV4_power /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/CMakeFiles/erase_flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/erase_flash.dir/depend

