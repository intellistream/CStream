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
include esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/depend.make

# Include the progress variables for this target.
include esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/flags.make

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.obj: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/flags.make
esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.obj: /home/tony/esp/esp-idf/components/touch_element/touch_element.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_touch_element.dir/touch_element.c.obj -c /home/tony/esp/esp-idf/components/touch_element/touch_element.c

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_touch_element.dir/touch_element.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/touch_element/touch_element.c > CMakeFiles/__idf_touch_element.dir/touch_element.c.i

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_touch_element.dir/touch_element.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/touch_element/touch_element.c -o CMakeFiles/__idf_touch_element.dir/touch_element.c.s

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.obj: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/flags.make
esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.obj: /home/tony/esp/esp-idf/components/touch_element/touch_button.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_touch_element.dir/touch_button.c.obj -c /home/tony/esp/esp-idf/components/touch_element/touch_button.c

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_touch_element.dir/touch_button.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/touch_element/touch_button.c > CMakeFiles/__idf_touch_element.dir/touch_button.c.i

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_touch_element.dir/touch_button.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/touch_element/touch_button.c -o CMakeFiles/__idf_touch_element.dir/touch_button.c.s

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/flags.make
esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj: /home/tony/esp/esp-idf/components/touch_element/touch_slider.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj -c /home/tony/esp/esp-idf/components/touch_element/touch_slider.c

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_touch_element.dir/touch_slider.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/touch_element/touch_slider.c > CMakeFiles/__idf_touch_element.dir/touch_slider.c.i

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_touch_element.dir/touch_slider.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/touch_element/touch_slider.c -o CMakeFiles/__idf_touch_element.dir/touch_slider.c.s

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/flags.make
esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj: /home/tony/esp/esp-idf/components/touch_element/touch_matrix.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj -c /home/tony/esp/esp-idf/components/touch_element/touch_matrix.c

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_touch_element.dir/touch_matrix.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/touch_element/touch_matrix.c > CMakeFiles/__idf_touch_element.dir/touch_matrix.c.i

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_touch_element.dir/touch_matrix.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/touch_element/touch_matrix.c -o CMakeFiles/__idf_touch_element.dir/touch_matrix.c.s

# Object files for target __idf_touch_element
__idf_touch_element_OBJECTS = \
"CMakeFiles/__idf_touch_element.dir/touch_element.c.obj" \
"CMakeFiles/__idf_touch_element.dir/touch_button.c.obj" \
"CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj" \
"CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj"

# External object files for target __idf_touch_element
__idf_touch_element_EXTERNAL_OBJECTS =

esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_element.c.obj
esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_button.c.obj
esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_slider.c.obj
esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/touch_matrix.c.obj
esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/build.make
esp-idf/touch_element/libtouch_element.a: esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libtouch_element.a"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && $(CMAKE_COMMAND) -P CMakeFiles/__idf_touch_element.dir/cmake_clean_target.cmake
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_touch_element.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/build: esp-idf/touch_element/libtouch_element.a

.PHONY : esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/build

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/clean:
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element && $(CMAKE_COMMAND) -P CMakeFiles/__idf_touch_element.dir/cmake_clean.cmake
.PHONY : esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/clean

esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/esp-idf/components/touch_element /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element /home/tony/esp/IOMTV4_power/build/esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/touch_element/CMakeFiles/__idf_touch_element.dir/depend

