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
include esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/depend.make

# Include the progress variables for this target.
include esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj: /home/tony/esp/esp-idf/components/esp32s2/cache_err_int.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/cache_err_int.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/cache_err_int.c > CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/cache_err_int.c -o CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.obj: /home/tony/esp/esp-idf/components/esp32s2/memprot.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/memprot.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/memprot.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/memprot.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/memprot.c > CMakeFiles/__idf_esp32s2.dir/memprot.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/memprot.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/memprot.c -o CMakeFiles/__idf_esp32s2.dir/memprot.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.obj: /home/tony/esp/esp-idf/components/esp32s2/clk.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/clk.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/clk.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/clk.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/clk.c > CMakeFiles/__idf_esp32s2.dir/clk.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/clk.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/clk.c -o CMakeFiles/__idf_esp32s2.dir/clk.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj: /home/tony/esp/esp-idf/components/esp32s2/crosscore_int.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/crosscore_int.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/crosscore_int.c > CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/crosscore_int.c -o CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj: /home/tony/esp/esp-idf/components/esp32s2/dport_access.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/dport_access.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/dport_access.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/dport_access.c > CMakeFiles/__idf_esp32s2.dir/dport_access.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/dport_access.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/dport_access.c -o CMakeFiles/__idf_esp32s2.dir/dport_access.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj: /home/tony/esp/esp-idf/components/esp32s2/hw_random.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/hw_random.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/hw_random.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/hw_random.c > CMakeFiles/__idf_esp32s2.dir/hw_random.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/hw_random.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/hw_random.c -o CMakeFiles/__idf_esp32s2.dir/hw_random.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.obj: /home/tony/esp/esp-idf/components/esp32s2/spiram.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/spiram.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/spiram.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/spiram.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/spiram.c > CMakeFiles/__idf_esp32s2.dir/spiram.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/spiram.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/spiram.c -o CMakeFiles/__idf_esp32s2.dir/spiram.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj: /home/tony/esp/esp-idf/components/esp32s2/spiram_psram.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/spiram_psram.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/spiram_psram.c > CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/spiram_psram.c -o CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj: /home/tony/esp/esp-idf/components/esp32s2/system_api_esp32s2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/system_api_esp32s2.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/system_api_esp32s2.c > CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/system_api_esp32s2.c -o CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj: /home/tony/esp/esp-idf/components/esp32s2/esp_crypto_lock.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/esp_crypto_lock.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/esp_crypto_lock.c > CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/esp_crypto_lock.c -o CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj: /home/tony/esp/esp-idf/components/esp32s2/esp_hmac.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/esp_hmac.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/esp_hmac.c > CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/esp_hmac.c -o CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.s

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/flags.make
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj: /home/tony/esp/esp-idf/components/esp32s2/esp_ds.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj -c /home/tony/esp/esp-idf/components/esp32s2/esp_ds.c

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp32s2.dir/esp_ds.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/esp32s2/esp_ds.c > CMakeFiles/__idf_esp32s2.dir/esp_ds.c.i

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp32s2.dir/esp_ds.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/esp32s2/esp_ds.c -o CMakeFiles/__idf_esp32s2.dir/esp_ds.c.s

# Object files for target __idf_esp32s2
__idf_esp32s2_OBJECTS = \
"CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/memprot.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/clk.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/spiram.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj" \
"CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj"

# External object files for target __idf_esp32s2
__idf_esp32s2_EXTERNAL_OBJECTS =

esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/cache_err_int.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/memprot.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clk.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/crosscore_int.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/dport_access.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/hw_random.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/spiram_psram.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/system_api_esp32s2.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_crypto_lock.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_hmac.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/esp_ds.c.obj
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/build.make
esp-idf/esp32s2/libesp32s2.a: esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C static library libesp32s2.a"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp32s2.dir/cmake_clean_target.cmake
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp32s2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/build: esp-idf/esp32s2/libesp32s2.a

.PHONY : esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/build

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clean:
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp32s2.dir/cmake_clean.cmake
.PHONY : esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/clean

esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/esp-idf/components/esp32s2 /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2 /home/tony/esp/IOMTV4_power/build/esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp32s2/CMakeFiles/__idf_esp32s2.dir/depend
