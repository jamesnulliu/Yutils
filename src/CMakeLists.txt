cmake_minimum_required(VERSION 3.21)

option(BUILD_SHARED_LIBS "Building using shared libraries." OFF)

set(LIBRARY_NAME Yutils) # Library name
set(LIBRARY_VERSION 1.0) # Library version

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(BUILD_SHARED_LIBS)
    message(STATUS "Building shared library")
    add_library(${LIBRARY_NAME} SHARED ${SOURCES})
    target_compile_definitions(${LIBRARY_NAME} PRIVATE YUTILS_EXPORT)
else()
    add_library(${LIBRARY_NAME} STATIC ${SOURCES})
endif()

# Specify include directories for this target
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Set the version of the library and output directories
set_target_properties(${LIBRARY_NAME} PROPERTIES
    VERSION ${LIBRARY_VERSION}
    OUTPUT_NAME ${LIBRARY_NAME}
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)