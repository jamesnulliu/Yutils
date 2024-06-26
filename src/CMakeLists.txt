# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# Library name: Yutils
set(LIB_NAME Yutils)

# Library version: 1.0
set(LIB_VERSION 1.0)

# Whether to build Yutils as a shared library
option(BUILD_SHARED_LIBS "Building using shared libraries." OFF)
if(BUILD_SHARED_LIBS)
    message(STATUS "[Yutils] Building as a shared library.")
else()
    message(STATUS "[Yutils] Building as a static library."
            " To build as a shared library, set BUILD_SHARED_LIBS to ON.")
endif()

# Collect all source files
file(
    GLOB_RECURSE 
    YUTILS_SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/Yutils/*.cpp"
)

# Create Library
add_library(${LIB_NAME} ${YUTILS_SRCS})

# Add macros for shared library
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${LIB_NAME} PRIVATE YUTILS_EXPORT)
endif()

# Include directories
target_include_directories(
    ${LIB_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Set the version of the library and output directories
set_target_properties(
    ${LIB_NAME} PROPERTIES
    VERSION ${LIB_VERSION}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib
)

# Copy the include directory to the output directory
add_custom_command(
    TARGET ${LIB_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${OUTPUT_DIR}/include
)