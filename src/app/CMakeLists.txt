# Include this module's public headers
target_include_directories(g491re_baremetal.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)

# Module sources
set(APP_SOURCES
    app.c
)

# Add to parent target
target_sources(g491re_baremetal.elf PRIVATE ${APP_SOURCES})