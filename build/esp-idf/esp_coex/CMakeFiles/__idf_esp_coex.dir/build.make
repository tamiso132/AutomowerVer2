# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/tom/projects/automower

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/projects/automower/build

# Include any dependencies generated for this target.
include esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/flags.make

esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj: esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/flags.make
esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj: /home/tom/esp/esp-idf/components/esp_coex/esp32/esp_coex_adapter.c
esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj: esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/projects/automower/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj"
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && /home/tom/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj -MF CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj.d -o CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj -c /home/tom/esp/esp-idf/components/esp_coex/esp32/esp_coex_adapter.c

esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.i"
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && /home/tom/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tom/esp/esp-idf/components/esp_coex/esp32/esp_coex_adapter.c > CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.i

esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.s"
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && /home/tom/.espressif/tools/xtensa-esp32-elf/esp-12.2.0_20230208/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tom/esp/esp-idf/components/esp_coex/esp32/esp_coex_adapter.c -o CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.s

# Object files for target __idf_esp_coex
__idf_esp_coex_OBJECTS = \
"CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj"

# External object files for target __idf_esp_coex
__idf_esp_coex_EXTERNAL_OBJECTS =

esp-idf/esp_coex/libesp_coex.a: esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/esp32/esp_coex_adapter.c.obj
esp-idf/esp_coex/libesp_coex.a: esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/build.make
esp-idf/esp_coex/libesp_coex.a: esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tom/projects/automower/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libesp_coex.a"
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_coex.dir/cmake_clean_target.cmake
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_coex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/build: esp-idf/esp_coex/libesp_coex.a
.PHONY : esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/build

esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/clean:
	cd /home/tom/projects/automower/build/esp-idf/esp_coex && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_coex.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/clean

esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/depend:
	cd /home/tom/projects/automower/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/projects/automower /home/tom/esp/esp-idf/components/esp_coex /home/tom/projects/automower/build /home/tom/projects/automower/build/esp-idf/esp_coex /home/tom/projects/automower/build/esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : esp-idf/esp_coex/CMakeFiles/__idf_esp_coex.dir/depend

