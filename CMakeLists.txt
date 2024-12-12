# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Project name
project(Yutils VERSION 1.1.0)

# Common utility functions:
include(${PROJECT_SOURCE_DIR}/cmake/utils/common.cmake)

set_default_values(
    YUTILS_BUILD_EXAMPLES ON 
    PROJECT_NAMESPACE "Yutils::"
)

# Utility functions for installing libraries:
include(${PROJECT_SOURCE_DIR}/cmake/utils/lib-install.cmake)

# Compiler configurations for cpp, e.g., g++, clang++, msvc(cl), etc.
include(${PROJECT_SOURCE_DIR}/cmake/compilers/cxx-compiler-configs.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/libraries/libspdlog.cmake)

set(CMAKE_EXECUTABLE_SUFFIX ".exe")

# Yutils library ---------------------------------------------------------------
add_subdirectory(lib)

# Examples ---------------------------------------------------------------------
if(YUTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


