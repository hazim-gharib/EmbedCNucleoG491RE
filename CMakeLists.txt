cmake_minimum_required(VERSION 3.15)
project(EmbedCNucleoG491RE C ASM)

# You must configure with:
# cmake -B build -S . -G Ninja -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please configure with -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

# Default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(SECTION_FLAGS "-ffunction-sections -fdata-sections")
set(WARN_FLAGS "-Wall -Wextra -Wshadow -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wconversion -Wdouble-promotion -Wformat=2 -Werror=return-type")

set(CMAKE_C_FLAGS_DEBUG "${MCU_FLAGS} -Og -g3 ${SECTION_FLAGS} ${WARN_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${MCU_FLAGS} -O2 -g0 ${SECTION_FLAGS} ${WARN_FLAGS}")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} ${SECTION_FLAGS} -Wl,--gc-sections")

# ---------------------------------------------------------------------------
# Core system / startup sources
# ---------------------------------------------------------------------------
set(SYSTEM_SOURCES
    main.c
    board/g491re/system_stm32g4xx.c
    board/g491re/sysmem.c
    board/g491re/syscalls.c
    board/g491re/startup_stm32g491xx.s
)

set_source_files_properties(
    board/g491re/startup_stm32g491xx.s
    PROPERTIES LANGUAGE ASM
)

# ---------------------------------------------------------------------------
# HAL Driver Sources
# ---------------------------------------------------------------------------
file(GLOB HAL_SOURCES
    vendor/STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Src/*.c
)
# Remove legacy files (optional)
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_legacy.c$")

# ---------------------------------------------------------------------------
# Create executable
# ---------------------------------------------------------------------------
add_executable(${PROJECT_NAME}.elf
    ${SYSTEM_SOURCES}
    ${HAL_SOURCES}
)
# ---------------------------------------------------------------------------
# Include dirs
# ---------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/app/public_inc
    ${CMAKE_SOURCE_DIR}/board/g491re/public_inc
    ${CMAKE_SOURCE_DIR}/board/g491re
    ${CMAKE_SOURCE_DIR}/bsp/public_inc
)

# Treat vendor headers as SYSTEM to demote warnings originating from third-party code
target_include_directories(${PROJECT_NAME}.elf SYSTEM PRIVATE
    vendor/STM32CubeG4/Drivers/CMSIS/Include
    vendor/STM32CubeG4/Drivers/CMSIS/Device/ST/STM32G4xx/Include
    vendor/STM32CubeG4/Drivers/STM32G4xx_HAL_Driver/Inc
)

# ---------------------------------------------------------------------------
# MCU DEFINES
# ---------------------------------------------------------------------------
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    STM32G491xx
    USE_HAL_DRIVER
)

# ---------------------------------------------------------------------------
# Linker Script
# ---------------------------------------------------------------------------
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/board/g491re/STM32G491RETX_FLASH.ld)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
)

# ---------------------------------------------------------------------------
# Add modules
# ---------------------------------------------------------------------------
add_subdirectory(app)
add_subdirectory(board/g491re)
add_subdirectory(bsp)

# ---------------------------------------------------------------------------
# Post-build steps
# ---------------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMENT "Generating HEX, BIN, and size report"
)

add_custom_target(report-size
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Size report"
)
