add_library(src INTERFACE)

target_sources(src INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/ExampleRenderer.cpp
        )

target_include_directories(src INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )