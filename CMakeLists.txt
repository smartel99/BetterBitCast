cmake_minimum_required(VERSION 3.18)

enable_language(CXX)

# We will hit 1.0.0 when we have a stable API
# We will hit 0.1.0 when we have finished the basic API
set(BBC_BUILD_VERSION 0.0.1)
set(INTERNAL_PROJ_DEFAULT_NAME bbc)

project(${INTERNAL_PROJ_DEFAULT_NAME} VERSION ${BBC_BUILD_VERSION})

set(is_root_project OFF) # Identifies if this is the root project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(is_root_project ON)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TO THE IMPLEMENTOR: If BBC_BUILD_TEST is set to OFF then googletest can be deleted from the vendor folder.
option(BBC_BUILD_TEST "Build bbc tests" ${is_root_project})

add_library(${PROJECT_NAME}-compile-options INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME}-compile-options ALIAS ${PROJECT_NAME}-compile-options)

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(${PROJECT_NAME}-compile-options INTERFACE
            -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
    )
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(${PROJECT_NAME}-compile-options INTERFACE
            /W4 /Wall /WX /permissive- /Zc:__cplusplus
    )
endif ()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} INTERFACE "$<BUILD_INTERFACE:${bbc_headers}>")

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_link_libraries(${PROJECT_NAME} INTERFACE
        ${PROJECT_NAME}::${PROJECT_NAME}-compile-options
)

add_subdirectory(vendor)
if (BBC_BUILD_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()
