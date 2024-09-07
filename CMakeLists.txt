# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils VERSION 1.1.0)

set(YUTILS_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Some Logger functions --------------------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/Logging.cmake)

# Arguments --------------------------------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/Arguments.cmake)

# Compiler and Linker Configurations -------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/Compiler.cmake)

# Library Install Utilities ----------------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/InstallLibraries.cmake)

# Yutils library ---------------------------------------------------------------
add_subdirectory(src)

# Examples ---------------------------------------------------------------------
if(YUTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


