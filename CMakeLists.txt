# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils VERSION 1.1.0)

# Some Logger functions --------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/Logging.cmake)

# Arguments --------------------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/Arguments.cmake)

# Compiler and Linker Configurations -------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)

# Library Install Utilities ----------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/InstallLibraries.cmake)

# Yutils library ---------------------------------------------------------------
add_subdirectory(src)

# Examples ---------------------------------------------------------------------
if(YUTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


