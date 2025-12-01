# Include this module's public headers
target_include_directories(g491re_baremetal.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)

# Module sources
set(BOARD_SOURCES
    gpio.c
    rcc.c
    board.c
)

# Add to parent target
target_sources(g491re_baremetal.elf PRIVATE ${BOARD_SOURCES})