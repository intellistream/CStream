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

# Include any dependencies generated for this target.
include esp-idf/cfp/CMakeFiles/__idf_cfp.dir/depend.make

# Include the progress variables for this target.
include esp-idf/cfp/CMakeFiles/__idf_cfp.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/cfp/CMakeFiles/__idf_cfp.dir/flags.make

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.obj: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/flags.make
esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.obj: /home/tony/esp/esp-idf/components/cfp/cfp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_cfp.dir/cfp.c.obj -c /home/tony/esp/esp-idf/components/cfp/cfp.c

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_cfp.dir/cfp.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/cfp/cfp.c > CMakeFiles/__idf_cfp.dir/cfp.c.i

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_cfp.dir/cfp.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/cfp/cfp.c -o CMakeFiles/__idf_cfp.dir/cfp.c.s

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.obj: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/flags.make
esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.obj: /home/tony/esp/esp-idf/components/cfp/tdppack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_cfp.dir/tdppack.c.obj -c /home/tony/esp/esp-idf/components/cfp/tdppack.c

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_cfp.dir/tdppack.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/cfp/tdppack.c > CMakeFiles/__idf_cfp.dir/tdppack.c.i

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_cfp.dir/tdppack.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/cfp/tdppack.c -o CMakeFiles/__idf_cfp.dir/tdppack.c.s

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.obj: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/flags.make
esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.obj: /home/tony/esp/esp-idf/components/cfp/u32frame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_cfp.dir/u32frame.c.obj -c /home/tony/esp/esp-idf/components/cfp/u32frame.c

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_cfp.dir/u32frame.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/cfp/u32frame.c > CMakeFiles/__idf_cfp.dir/u32frame.c.i

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_cfp.dir/u32frame.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/cfp/u32frame.c -o CMakeFiles/__idf_cfp.dir/u32frame.c.s

# Object files for target __idf_cfp
__idf_cfp_OBJECTS = \
"CMakeFiles/__idf_cfp.dir/cfp.c.obj" \
"CMakeFiles/__idf_cfp.dir/tdppack.c.obj" \
"CMakeFiles/__idf_cfp.dir/u32frame.c.obj"

# External object files for target __idf_cfp
__idf_cfp_EXTERNAL_OBJECTS =

esp-idf/cfp/libcfp.a: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/cfp.c.obj
esp-idf/cfp/libcfp.a: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/tdppack.c.obj
esp-idf/cfp/libcfp.a: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/u32frame.c.obj
esp-idf/cfp/libcfp.a: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/build.make
esp-idf/cfp/libcfp.a: esp-idf/cfp/CMakeFiles/__idf_cfp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libcfp.a"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && $(CMAKE_COMMAND) -P CMakeFiles/__idf_cfp.dir/cmake_clean_target.cmake
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_cfp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/cfp/CMakeFiles/__idf_cfp.dir/build: esp-idf/cfp/libcfp.a

.PHONY : esp-idf/cfp/CMakeFiles/__idf_cfp.dir/build

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/clean:
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/cfp && $(CMAKE_COMMAND) -P CMakeFiles/__idf_cfp.dir/cmake_clean.cmake
.PHONY : esp-idf/cfp/CMakeFiles/__idf_cfp.dir/clean

esp-idf/cfp/CMakeFiles/__idf_cfp.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/esp-idf/components/cfp /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/esp-idf/cfp /home/tony/esp/IOMTV4_power/build/esp-idf/cfp/CMakeFiles/__idf_cfp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/cfp/CMakeFiles/__idf_cfp.dir/depend

