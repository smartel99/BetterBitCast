if (NOT DEFINED INTERNAL_PROJ_DEFAULT_NAME)
    message(FATAL_ERROR "INTERNAL_PROJ_DEFAULT_NAME is not defined. Did you somehow include this file directly without the main CMakeLists.txt being called first?")
endif ()

cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(${INTERNAL_PROJ_DEFAULT_NAME}-test)

if(NOT TARGET ${INTERNAL_PROJ_DEFAULT_NAME})
    find_package(${INTERNAL_PROJ_DEFAULT_NAME} CONFIG REQUIRED)
endif()


add_library(${PROJECT_NAME} STATIC)
add_library(${INTERNAL_PROJ_DEFAULT_NAME}::test ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC
        bbc::bbc
        gtest::gtest
        ${INTERNAL_PROJ_DEFAULT_NAME}::vendor
)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_sources(${PROJECT_NAME} PRIVATE
        bbc_test_main.cpp
)

add_executable(${PROJECT_NAME}-basic)
target_sources(${PROJECT_NAME}-basic PRIVATE
        basic/primitives.cpp
)
target_link_libraries(${PROJECT_NAME}-basic PRIVATE
        bbc::test
        gtest::gtest
)

if(CCMATH_OS_WINDOWS)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Only supported compilers currently are MSVC, GNU and Clang
if(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC
            /W4 /WX
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    target_compile_options(${PROJECT_NAME} PUBLIC
            -Wall -Wextra -Wno-pedantic -Wno-unused-function
    )
endif()


add_test(NAME ${PROJECT_NAME}-basic COMMAND ${PROJECT_NAME}-basic)
