# ==============================================================================
# @file Compiler.cmake
# @brief Global compiler settings for the whole project.
# ==============================================================================

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions("YUTILS_COMPILER_MSVC")
    add_compile_options(/permissive- /Zc:forScope /openmp)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions("YUTILS_COMPILER_CLANG")
    # add_compile_options(-fopenmp)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions("YUTILS_COMPILER_GNU")
    add_compile_options(-fopenmp) 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
else()
    log_fatal("Unsupported compiler")
endif()

## I don't really want to define compiler versions...
# string(REPLACE "." ";" YUTILS_COMPILER_VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
# list(GET YUTILS_COMPILER_VERSION_LIST 0 YUTILS_COMPILER_MAJOR_VERSION)
# list(GET YUTILS_COMPILER_VERSION_LIST 1 YUTILS_COMPILER_MINOR_VERSION)
# list(GET YUTILS_COMPILER_VERSION_LIST 2 YUTILS_COMPILER_PATCH_VERSION)
# add_compile_definitions("YUTILS_COMPILER_MAJOR_VERSION=${YUTILS_COMPILER_MAJOR_VERSION}")
# add_compile_definitions("YUTILS_COMPILER_MINOR_VERSION=${YUTILS_COMPILER_MINOR_VERSION}")
# add_compile_definitions("YUTILS_COMPILER_PATCH_VERSION=${YUTILS_COMPILER_PATCH_VERSION}")