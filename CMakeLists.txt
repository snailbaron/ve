cmake_minimum_required(VERSION 3.12)

project(ve)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(VE_BUILD_EXAMPLES "Build examples for ve library" ON)
option(VE_BUILD_TESTS "Build tests for ve library" ON)

add_library(ve INTERFACE)
target_include_directories(ve INTERFACE include)

if(VE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(VE_BUILD_TESTS)
    if(NOT TARGET Catch2::Catch2)
        add_subdirectory(deps/Catch2)
    endif()

    enable_testing()
    add_subdirectory(tests)
endif()
