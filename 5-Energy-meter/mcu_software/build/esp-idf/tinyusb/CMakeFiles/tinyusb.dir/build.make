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
include esp-idf/tinyusb/CMakeFiles/tinyusb.dir/depend.make

# Include the progress variables for this target.
include esp-idf/tinyusb/CMakeFiles/tinyusb.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj: /home/tony/esp/esp-idf/components/tinyusb/additions/src/descriptors_control.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/additions/src/descriptors_control.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/additions/src/descriptors_control.c > CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/additions/src/descriptors_control.c -o CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj: /home/tony/esp/esp-idf/components/tinyusb/additions/src/tinyusb.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/additions/src/tinyusb.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/additions/src/tinyusb.c > CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/additions/src/tinyusb.c -o CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj: /home/tony/esp/esp-idf/components/tinyusb/additions/src/tusb_tasks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/additions/src/tusb_tasks.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/additions/src/tusb_tasks.c > CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/additions/src/tusb_tasks.c -o CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj: /home/tony/esp/esp-idf/components/tinyusb/additions/src/usb_descriptors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/additions/src/usb_descriptors.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/additions/src/usb_descriptors.c > CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/additions/src/usb_descriptors.c -o CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c > CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c -o CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/cdc/cdc_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/cdc/cdc_device.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/cdc/cdc_device.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/cdc/cdc_device.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/hid/hid_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/hid/hid_device.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/hid/hid_device.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/hid/hid_device.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/midi/midi_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/midi/midi_device.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/midi/midi_device.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/midi/midi_device.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/msc/msc_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/msc/msc_device.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/msc/msc_device.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/msc/msc_device.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/tony/coms.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/tony/coms.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/tony/coms.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/tony/coms.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/vendor/vendor_device.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/vendor/vendor_device.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/vendor/vendor_device.c > CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/class/vendor/vendor_device.c -o CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/common/tusb_fifo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/common/tusb_fifo.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/common/tusb_fifo.c > CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/common/tusb_fifo.c -o CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd_control.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd_control.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd_control.c > CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd_control.c -o CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd.c > CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/device/usbd.c -o CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.s

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/flags.make
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj: /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/tusb.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj -c /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/tusb.c

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/tusb.c > CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.i

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/tinyusb/tinyusb/src/tusb.c -o CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.s

# Object files for target tinyusb
tinyusb_OBJECTS = \
"CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj" \
"CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj" \
"CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj" \
"CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj" \
"CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj"

# External object files for target tinyusb
tinyusb_EXTERNAL_OBJECTS =

esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/descriptors_control.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tinyusb.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/tusb_tasks.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/additions/src/usb_descriptors.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/cdc/cdc_device.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/hid/hid_device.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/midi/midi_device.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/msc/msc_device.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/tony/coms.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/class/vendor/vendor_device.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/common/tusb_fifo.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd_control.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/device/usbd.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/tinyusb/src/tusb.c.obj
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/build.make
esp-idf/tinyusb/libtinyusb.a: esp-idf/tinyusb/CMakeFiles/tinyusb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX static library libtinyusb.a"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && $(CMAKE_COMMAND) -P CMakeFiles/tinyusb.dir/cmake_clean_target.cmake
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinyusb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/tinyusb/CMakeFiles/tinyusb.dir/build: esp-idf/tinyusb/libtinyusb.a

.PHONY : esp-idf/tinyusb/CMakeFiles/tinyusb.dir/build

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/clean:
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb && $(CMAKE_COMMAND) -P CMakeFiles/tinyusb.dir/cmake_clean.cmake
.PHONY : esp-idf/tinyusb/CMakeFiles/tinyusb.dir/clean

esp-idf/tinyusb/CMakeFiles/tinyusb.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/esp-idf/components/tinyusb /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb /home/tony/esp/IOMTV4_power/build/esp-idf/tinyusb/CMakeFiles/tinyusb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/tinyusb/CMakeFiles/tinyusb.dir/depend

