# Include this module's public headers
target_include_directories(EmbedCNucleoG491RE.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)

# Module sources
set(BSP_SOURCES
    bsp_gpio.c
)

# Add to parent target
target_sources(EmbedCNucleoG491RE.elf PRIVATE ${BSP_SOURCES})