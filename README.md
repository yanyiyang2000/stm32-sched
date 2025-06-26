# Table of Contents
- [Overview](#overview)
- [Prerequisites](#prerequisites)
- [Porting to other Cortex Devices](#porting-to-other-cortex-devices)
- [Setting Project Name](#setting-project-name)
- [Building](#building)
- [Flashing](#flashing)
- [Cleaning](#cleaning)
- [Debugging](#debugging)
    - [Session 1](#session-1)
    - [Session 2](#session-2)
- [Frequently Used GDB Commands](#frequently-used-gdb-commands)
- [Frequently Used GCC Commands](#frequently-used-gcc-commands)
- [References](#references)


# Overview
This project contains a task scheduler targeting ARMv7E-M devices.

The followings are the hardware, toolchain and build system used by the project.
| Property             | Value                                    |
| -------------------- | ---------------------------------------- |
| Development board    | STM32 Nucleo-64 w/ embedded ST-LINK/v2-1 |
| MCU                  | STM32L476RG                              |
| MCU series           | STM32L4                                  |
| MCU CPU core         | ARM Cortex-M4                            |
| MCU CPU architecture | ARMv7E-M                                 |
| Toolchain            | gcc                                      |
| Build system         | cmake                                    |

The project's source code is divided into two major directories:
- The `CMSIS` directory contains header files and source code provided by [ARM](https://github.com/ARM-software/CMSIS_6/tree/main/CMSIS/Core) and [STMicroelectronics](https://github.com/STMicroelectronics/cmsis_device_l4) that are conforming to [CMSIS 6](https://arm-software.github.io/CMSIS_6/latest/General/index.html).
- The `User` directory contains header files and source code for the demonstractions and C runtime startup code (`crt0.S`).


# Prerequisites
Install the following packages (on Debian 12):
- `gcc-arm-none-eabi`
- `binutils-arm-none-eabi`
- `libnewlib-arm-none-eabi`
- `gdb-multiarch`
- `cmake`
- `make`
- `openocd`


# Porting to other Cortex Devices
Based on the properties of the target device, replace the following files:
| File                   | Depends on             | Source |
| ---------------------- | ---------------------- | ------ |
| `core_cm4.h`           | MCU CPU core           | ARM    |
| `armv7m_mpu.h`         | MCU CPU architecture   | ARM    |
| `cmsis_gcc.h`          | Toolchain              | ARM    |
| `cmsis_gcc_m.h`        | Toolchain & MCU core   | ARM    |
| `stm32l4xx_gcc.ld`[^1] | Toolchain & MCU series | ST     |
| `stm32l476xx.h`        | MCU                    | ST     |
| `stm32l4xx.h`          | MCU series             | ST     |
| `startup_stm32l4xx.c`  | MCU series             | ST     |
| `system_stm32l4xx.c`   | MCU series             | ST     |
| `STM32L476.svd`        | MCU                    | ST     |
[^1]: You may need to modify the linker script using correct FLASH and RAM size.

> [!NOTE]
> Modify the compile definitions, compile options and link options in the top-level `CMakeLists.txt` based on the properties of the target device.


# Setting Project Name and Executable Name
In the project root directory, modify the `<PROJECT_NAME>` entry in `CMakeLists.txt`:
```cmake
project(
    <PROJECT_NAME>
    LANGUAGES C ASM
)
```

In the `User` directory, modify the `<EXE_NAME>` entry in `CMakeLists.txt`:
```cmake
add_executable(
    <EXE_NAME>
    ...
)

target_include_directories(
    <EXE_NAME>
    ...
)
```


# Building
In the project root directory, run the `build.sh` script to build the firmware.
> [!NOTE]
> Modify the `BUILD_TYPE` variable in the script for debug or release build. The default build type is `Debug`.


# Flashing
In the project root directory, use the following command:
```shell
openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program ./build/User/<EXE_NAME>.elf verify reset exit"
```
> [!NOTE]
> Select the appropriate interface and target to replace `interface/stlink.cfg` and `target/stm32l4x.cfg` when porting this project to other devices.


# Cleaning
In the project root directory, use the following command:
```shell
rm -rf ./build
```


# Debugging
The debugging process requires two shell sessions.

## Session 1
In any directory, create a shell session and use the following command:
```shell
openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "gdb_port 3333"
```
> [!NOTE]
> Select the appropriate interface and target to replace `interface/stlink.cfg` and `target/stm32l4x.cfg` when porting this project to other devices.

## Session 2
In the project root directory, create another shell session and use the following command:
```shell
gdb-multiarch ./build/User/<EXE_NAME>.elf
```
After seeing the prompt from GDB, use the following command:
```shell
target remote localhost:3333
```


# Frequently Used GDB Commands
| Command              | Description                            |
| -------------------- | -------------------------------------- |
| `monitor reset halt` | Reset and halt                         |
| `i b`                | List all breakpoints                   |
| `d 2`                | Delete breakpoint 2                    |
| `b foo.c:18`         | Set a breakpoint at line 18 of `foo.c` |
| `p foo`              | Print `foo` in decimal format          |
| `p/t foo`            | Print `foo` in binary format           |
| `p/x foo`            | Print `foo` in hexadecimal format      |
| `c`                  | Continue                               |
| `s`                  | Step into                              |
| `n`                  | Step over                              |
| `bt`                 | Print trace of all frames              |


# Frequently Used GCC Commands
| Command                                                    | Description                 |
| ---------------------------------------------------------- | --------------------------- |
| `arm-none-eabi-gcc <COMPILER_OPTIONS> -E -dM -< /dev/null` | Show predefined macros      |
| `arm-none-eabi-objdump -d <EXE_NAME>.elf`                  | View the assembly code      |
| `arm-none-eabi-objdump -t <EXE_NAME>.elf`                  | View the symbol table       |
| `arm-none-eabi-readelf -S <EXE_NAME>.elf`                  | View the output info        |
| `arm-none-eabi-size <EXE_NAME>.elf`                        | View the size of executable |


# References
- [ARMv7-M Architecture Reference Manual (DDI 0403)](https://developer.arm.com/documentation/ddi0403/latest/)
- [Cortex-M4 Devices Generic User Guide (DUI 0553)](https://developer.arm.com/documentation/dui0553/latest/)
- [STM32L47xxx Reference Manual (RM0351)](https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32L476xx Datasheet (DS10198)](https://www.st.com/resource/en/datasheet/stm32l476je.pdf)
- [STM32 Nucleo-64 Boards User Manual (UM1724)](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
