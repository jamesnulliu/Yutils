# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils)

# Some Logger functions --------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Logger.cmake)

# Compiler and Linker Configurations -------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Compiler.cmake)

# Global Output directory ------------------------------------------------------
if (NOT DEFINED OUTPUT_DIR)
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()
log_info("Output Directory: ${OUTPUT_DIR}.")

# Global Build type ------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
log_info("Build Type: ${CMAKE_BUILD_TYPE}.")

# Shared or Static Library -----------------------------------------------------
option(BUILD_SHARED_LIBS "Building a shared library." OFF)

# Yutils library ---------------------------------------------------------------
add_subdirectory(src)

# Examples ---------------------------------------------------------------------
option(BUILD_EXAMPLES "Build the tests" ON)
if(BUILD_EXAMPLES)
    log_info("Building Examples.")
    add_subdirectory(examples)
endif()


