# @Path: Yutils/src/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Library name: Yutils
set(LibraryName Yutils)
# Library version: 1.0
set(LibraryVersion 1.0)

# Get all source files
file(GLOB_RECURSE Sources "${CMAKE_CURRENT_SOURCE_DIR}/Yutils/*.cpp")

# Build shared or static library
# @see Yutils/CMakeLists.txt: option(BUILD_SHARED_LIBS ...)
if(BUILD_SHARED_LIBS)
    message(STATUS "[Yutils] Building shared library")
    add_library(${LibraryName} SHARED ${Sources})
    target_compile_definitions(${LibraryName} PRIVATE YUTILS_EXPORT)
else()
    message(STATUS "[Yutils] Building static library")
    add_library(${LibraryName} STATIC ${Sources})
endif()

# Specify include directories for this target
target_include_directories(${LibraryName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if (NOT DEFINED LIB_OUTPUT_DIR)
    set(LIB_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
endif()

message(STATUS "[Yutils] Library output directory: ${LIB_OUTPUT_DIR}")

# Set the version of the library and output directories
set_target_properties(
    ${LibraryName} PROPERTIES
    VERSION ${LibraryVersion}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
)