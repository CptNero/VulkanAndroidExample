cmake_minimum_required(VERSION 3.10.2)
project(native-lib)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../src)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../external)

add_library(native-app-glue
        STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        )

add_library(native-lib
        SHARED
        main.cpp
        )

target_include_directories(native-lib
        PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue
        ${SRC_DIR}/glm/glm
        ${SRC_DIR}/stb
        )

add_subdirectory(${SRC_DIR} ./src)
add_subdirectory(${EXTERNAL_DIR} ./external)

target_link_libraries(src
        INTERFACE
        external
        )

target_compile_definitions(native-lib
        PRIVATE
        VK_USE_PLATFORM_ANDROID_KHR
        )

target_compile_options(native-lib
        PRIVATE
        -Wall -Wextra -pedantic
        )

set_target_properties(native-lib
        PROPERTIES LINK_FLAGS "-u ANativeActivity_onCreate"
        )

target_link_libraries(native-lib PUBLIC
        native-app-glue
        android
        log
        vulkan
        external
        src
        )
