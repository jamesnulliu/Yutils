# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)
# Project name
project(Yutils)

# ==================================================================================================
# Compiler and Linker Configuration
# --------------------------------------------------------------------------------------------------
# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "[Yutils] C++ standard: ${CMAKE_CXX_STANDARD}")
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
# ==================================================================================================

# ==================================================================================================
# Target Configuration
# --------------------------------------------------------------------------------------------------
# Output directory for the build
if (NOT DEFINED OUTPUT_DIR)
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()
message(STATUS "[Yutils] Output directory: ${OUTPUT_DIR}")

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "[Yutils] Build type: ${CMAKE_BUILD_TYPE}")

# Yutils library -----------------------------------------------------------------------------------
add_subdirectory(src)

# Tests --------------------------------------------------------------------------------------------
option(BUILD_TESTS "Building tests." OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
# ==================================================================================================
