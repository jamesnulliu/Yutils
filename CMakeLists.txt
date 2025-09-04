# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils VERSION 1.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

set(YUTILS_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Some Logger functions --------------------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/utils/logging.cmake)

# Compiler and Linker Configurations -------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/compiler.cmake)

# Library Install Utilities ----------------------------------------------------
include(${YUTILS_PROJECT_DIR}/cmake/utils/lib-install.cmake)

# Yutils library ---------------------------------------------------------------
find_package(spdlog CONFIG REQUIRED)
add_subdirectory(lib)

# Examples ---------------------------------------------------------------------
option(YUTILS_BUILD_EXAMPLES "Whether to build the examples" ON)
log_info("|- Build Examples: ${YUTILS_BUILD_EXAMPLES}")
if(YUTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


