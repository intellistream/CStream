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
include esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/depend.make

# Include the progress variables for this target.
include esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/flags.make

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.obj: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/flags.make
esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.obj: /home/tony/esp/esp-idf/components/app_trace/app_trace.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_app_trace.dir/app_trace.c.obj -c /home/tony/esp/esp-idf/components/app_trace/app_trace.c

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_app_trace.dir/app_trace.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/app_trace/app_trace.c > CMakeFiles/__idf_app_trace.dir/app_trace.c.i

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_app_trace.dir/app_trace.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/app_trace/app_trace.c -o CMakeFiles/__idf_app_trace.dir/app_trace.c.s

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/flags.make
esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj: /home/tony/esp/esp-idf/components/app_trace/app_trace_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj -c /home/tony/esp/esp-idf/components/app_trace/app_trace_util.c

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_app_trace.dir/app_trace_util.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/app_trace/app_trace_util.c > CMakeFiles/__idf_app_trace.dir/app_trace_util.c.i

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_app_trace.dir/app_trace_util.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/app_trace/app_trace_util.c -o CMakeFiles/__idf_app_trace.dir/app_trace_util.c.s

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/flags.make
esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj: /home/tony/esp/esp-idf/components/app_trace/host_file_io.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj -c /home/tony/esp/esp-idf/components/app_trace/host_file_io.c

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_app_trace.dir/host_file_io.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/app_trace/host_file_io.c > CMakeFiles/__idf_app_trace.dir/host_file_io.c.i

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_app_trace.dir/host_file_io.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/app_trace/host_file_io.c -o CMakeFiles/__idf_app_trace.dir/host_file_io.c.s

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/flags.make
esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj: /home/tony/esp/esp-idf/components/app_trace/gcov/gcov_rtio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj -c /home/tony/esp/esp-idf/components/app_trace/gcov/gcov_rtio.c

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.i"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/esp/esp-idf/components/app_trace/gcov/gcov_rtio.c > CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.i

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.s"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && /home/tony/.espressif/tools/xtensa-esp32s2-elf/esp-2020r3-8.4.0/xtensa-esp32s2-elf/bin/xtensa-esp32s2-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/esp/esp-idf/components/app_trace/gcov/gcov_rtio.c -o CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.s

# Object files for target __idf_app_trace
__idf_app_trace_OBJECTS = \
"CMakeFiles/__idf_app_trace.dir/app_trace.c.obj" \
"CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj" \
"CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj" \
"CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj"

# External object files for target __idf_app_trace
__idf_app_trace_EXTERNAL_OBJECTS =

esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace.c.obj
esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/app_trace_util.c.obj
esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/host_file_io.c.obj
esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/gcov/gcov_rtio.c.obj
esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/build.make
esp-idf/app_trace/libapp_trace.a: esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tony/esp/IOMTV4_power/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libapp_trace.a"
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && $(CMAKE_COMMAND) -P CMakeFiles/__idf_app_trace.dir/cmake_clean_target.cmake
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_app_trace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/build: esp-idf/app_trace/libapp_trace.a

.PHONY : esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/build

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/clean:
	cd /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace && $(CMAKE_COMMAND) -P CMakeFiles/__idf_app_trace.dir/cmake_clean.cmake
.PHONY : esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/clean

esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/depend:
	cd /home/tony/esp/IOMTV4_power/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/esp/IOMTV4_power /home/tony/esp/esp-idf/components/app_trace /home/tony/esp/IOMTV4_power/build /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace /home/tony/esp/IOMTV4_power/build/esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/app_trace/CMakeFiles/__idf_app_trace.dir/depend
