# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build

# Include any dependencies generated for this target.
include CMakeFiles/ledtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ledtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ledtest.dir/flags.make

CMakeFiles/ledtest.dir/ledtest.c.o: CMakeFiles/ledtest.dir/flags.make
CMakeFiles/ledtest.dir/ledtest.c.o: ../ledtest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ledtest.dir/ledtest.c.o"
	/home/book/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ledtest.dir/ledtest.c.o   -c /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/ledtest.c

CMakeFiles/ledtest.dir/ledtest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ledtest.dir/ledtest.c.i"
	/home/book/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/ledtest.c > CMakeFiles/ledtest.dir/ledtest.c.i

CMakeFiles/ledtest.dir/ledtest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ledtest.dir/ledtest.c.s"
	/home/book/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/ledtest.c -o CMakeFiles/ledtest.dir/ledtest.c.s

CMakeFiles/ledtest.dir/ledtest.c.o.requires:

.PHONY : CMakeFiles/ledtest.dir/ledtest.c.o.requires

CMakeFiles/ledtest.dir/ledtest.c.o.provides: CMakeFiles/ledtest.dir/ledtest.c.o.requires
	$(MAKE) -f CMakeFiles/ledtest.dir/build.make CMakeFiles/ledtest.dir/ledtest.c.o.provides.build
.PHONY : CMakeFiles/ledtest.dir/ledtest.c.o.provides

CMakeFiles/ledtest.dir/ledtest.c.o.provides.build: CMakeFiles/ledtest.dir/ledtest.c.o


# Object files for target ledtest
ledtest_OBJECTS = \
"CMakeFiles/ledtest.dir/ledtest.c.o"

# External object files for target ledtest
ledtest_EXTERNAL_OBJECTS =

ledtest: CMakeFiles/ledtest.dir/ledtest.c.o
ledtest: CMakeFiles/ledtest.dir/build.make
ledtest: CMakeFiles/ledtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ledtest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ledtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ledtest.dir/build: ledtest

.PHONY : CMakeFiles/ledtest.dir/build

CMakeFiles/ledtest.dir/requires: CMakeFiles/ledtest.dir/ledtest.c.o.requires

.PHONY : CMakeFiles/ledtest.dir/requires

CMakeFiles/ledtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ledtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ledtest.dir/clean

CMakeFiles/ledtest.dir/depend:
	cd /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build /home/book/100ask_imx6ull_mini-sdk/Linux-4.9.88/DRIVER/linux_driver/led_drv_device_tree/ledtest/build/CMakeFiles/ledtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ledtest.dir/depend

