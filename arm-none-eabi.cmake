set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi)

# Prevent CMake from trying to run test programs on the host
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -O2 -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -specs=nosys.specs")

# Use nosys.specs to avoid references to host syscalls during linking
# (prevents undefined references to _read/_write/_sbrk/_exit during test links).
