cmake_minimum_required(VERSION 3.12)

project(ve)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(VE_BUILD_TESTS_AND_EXAMPLES "Build tests and examples for ve library" ON)

add_library(ve INTERFACE)
target_include_directories(ve INTERFACE include)

if(VE_BUILD_TESTS_AND_EXAMPLES)
    add_subdirectory(examples)

    if(NOT TARGET Catch2::Catch2)
        add_subdirectory(deps/Catch2)
    endif()
    enable_testing()
    add_subdirectory(tests)
endif()
