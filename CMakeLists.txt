cmake_minimum_required(VERSION 3.22)

# Uncomment to make cmake output verbose
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Skip compiler test for cross compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set compiler path
set(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER   "/usr/bin/arm-none-eabi-gcc")

# Set executable extension
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)

project(
    stm32-sched
    LANGUAGES C ASM
)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O3")

add_compile_definitions(
    STM32L476xx
)

add_compile_options(
    -mthumb
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=soft            # use software emulation for floating point operations
    -Wall                       # enable all warnings
    -Wno-missing-attributes     # disable warning about missing attributes
    -ffunction-sections         # place each function in its own named section in the output object file
    -fdata-sections             # place each data in its own named section in the output object file
)

add_link_options(
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=soft            # use software emulation for floating point operations
    -nostartfiles               # use custom crt0.S (otherwise newlib's crt0.S will be used)
    --specs=nano.specs          # use libc_nano.a (otherwise libc.a will be used)
    --specs=nosys.specs         # use libnosys.a (provides stub syscalls such as `_exit` used by the custom crt0.S)
    -Wl,--gc-sections           # enable garbage collection of unused sections
    -Wl,--trace                 # print name of input files (use --verbose for more detailed information)
    -Wl,--print-memory-usage    # print memory usage
    # -Wl,--print-map           # print memory map
    # -T "${PROJECT_SOURCE_DIR}/CMSIS/Device/ST/STM32L4xx/Config/stm32l4xx_gcc.ld"
    -T "${PROJECT_SOURCE_DIR}/User/Config/stm32l4xx_gcc.ld"
)

add_subdirectory(
    ${PROJECT_SOURCE_DIR}/User
)
