# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils)

# Some Logger functions --------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Logger.cmake)

# Arguments --------------------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Arguments.cmake)

# Compiler and Linker Configurations -------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Compiler.cmake)

# Shared or Static Library -----------------------------------------------------
option(BUILD_SHARED_LIBS "Building a shared library." OFF)

# Yutils library ---------------------------------------------------------------
add_subdirectory(src)

# Examples ---------------------------------------------------------------------
if(YUTILS_BUILD_EXAMPLES)
    log_info("Building Examples.")
    add_subdirectory(examples)
endif()


