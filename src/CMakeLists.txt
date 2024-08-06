# ==============================================================================
# @file src/CMakeLists.txt
# ==============================================================================

# Library name: "Yutils"
set(LIB_NAME Yutils)
# Library version: 1.0
set(LIB_VERSION 1.0)

# Collect all source files
file(GLOB_RECURSE YUTILS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

log_info("Yutils Source Files: [${YUTILS_SRCS}].")

# Create Library Target
add_library(${LIB_NAME} ${YUTILS_SRCS})

# Build Type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${LIB_NAME} PRIVATE DEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${LIB_NAME} PRIVATE RELEASE_BUILD)
else()
    log_fatal("Unsupported Build Type: ${CMAKE_BUILD_TYPE}.")
endif()

if(BUILD_SHARED_LIBS)
    log_info("Building a SHARED Library.")
else()
    log_info("Building a STATIC Library.")
endif()
# Shared or Static Library
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${LIB_NAME} PRIVATE YUTILS_EXPORT)
endif()

# Include directories
target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
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
    ${PROJECT_SOURCE_DIR}/include
    ${OUTPUT_DIR}/include
)