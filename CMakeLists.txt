# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)
# Project name and version
project(Yutils VERSION 0.1)

# Whether to build Yutils as a shared library
option(BUILD_SHARED_LIBS "Building using shared libraries." OFF)
# Whether to build "./tests" for testing
option(BUILD_TESTS "Building tests." OFF)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set defaut build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    # MSVC compiler-specific options
    add_compile_options(/permissive- /Zc:forScope)
else()
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

add_subdirectory(src)

if (BUILD_TESTS)
    # I don't know how to use GTest with CMake yet
    # > enable_testing()
    add_subdirectory(tests)
endif()