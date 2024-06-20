# @Path: Yutils/src/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Library name: Yutils
set(LIBRARY_NAME Yutils)
# Library version: 0.1
set(LIBRARY_VERSION 0.1)

# Get all source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Yutils/*.cpp")

# Build shared or static library
# @see Yutils/CMakeLists.txt: option(BUILD_SHARED_LIBS ...)
if(BUILD_SHARED_LIBS)
    message(STATUS "[Yutils] Building shared library")
    add_library(${LIBRARY_NAME} SHARED ${SOURCES})
    target_compile_definitions(${LIBRARY_NAME} PRIVATE YUTILS_EXPORT)
else()
    message(STATUS "[Yutils] Building static library")
    add_library(${LIBRARY_NAME} STATIC ${SOURCES})
endif()

# Specify include directories for this target
target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# set(LIB_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

message(STATUS "[Yutils] Library output directory: ${LIB_OUTPUT_DIR}")

# Set the version of the library and output directories
set_target_properties(
    ${LIBRARY_NAME} PROPERTIES
    VERSION ${LIBRARY_VERSION}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
)