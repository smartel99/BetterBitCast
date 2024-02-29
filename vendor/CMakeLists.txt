if (NOT DEFINED INTERNAL_PROJ_DEFAULT_NAME)
    message(FATAL_ERROR "INTERNAL_PROJ_DEFAULT_NAME is not defined. Did you somehow include this file directly without the main CMakeLists.txt being called first?")
endif ()

project(${INTERNAL_PROJ_DEFAULT_NAME}-vendor)

include(FetchContent)

set(BOOST_INCLUDE_LIBRARIES pfr)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
        boost_pfr
        GIT_REPOSITORY https://github.com/boostorg/pfr.git
        GIT_TAG 2.2.0
)
FetchContent_MakeAvailable(boost_pfr)

if (BBC_BUILD_TEST)
    # PThreads are not available on Windows
    # So tell gtest to not use them.
    if(BBC_WINDOWS)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
    endif()

    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_build_samples OFF CACHE BOOL "" FORCE)
    set(gtest_build_tests OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)

    add_library(gtest::gtest ALIAS gtest)
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${INTERNAL_PROJ_DEFAULT_NAME}::vendor ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} INTERFACE
        boost_pfr
)

if(BBC_BUILD_TEST)
    target_link_libraries(${PROJECT_NAME} INTERFACE
            gtest::gtest
    )
endif ()
