# ==============================================================================
# @file src/CMakeLists.txt
# ==============================================================================

# Library name: "Yutils"
set(LIB_NAME Yutils)
# Library version: 1.0
set(LIB_VERSION 1.0)

find_package(spdlog REQUIRED PATHS ${SPDLOG_DIR})

# Collect all source files
file(GLOB_RECURSE YUTILS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Controlled by ${BUILD_SHARED_LIBS} option
add_library(${LIB_NAME} ${YUTILS_SRCS})
add_library(Yutils::${LIB_NAME} ALIAS ${LIB_NAME})

# Set library version
set_target_properties(${LIB_NAME} PROPERTIES VERSION ${LIB_VERSION})

# Include directories
target_include_directories(
    ${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Build Type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${LIB_NAME} PRIVATE DEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${LIB_NAME} PRIVATE RELEASE_BUILD)
else()
    log_fatal("Unsupported Build Type: ${CMAKE_BUILD_TYPE}")
endif()

if(BUILD_SHARED_LIBS)  # Shared Library
    target_compile_definitions(${LIB_NAME} PRIVATE YUTILS_EXPORT)
    target_link_libraries(${LIB_NAME} PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
    target_compile_definitions(${LIB_NAME} INTERFACE YUTILS_IMPORT)
else()  # Static Library
    target_link_libraries(${LIB_NAME} PUBLIC spdlog::spdlog)
endif()

# Installations ===============================================================
# Install the library
install(
    TARGETS ${LIB_NAME}            
    EXPORT ${LIB_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
# Install header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
# Export the targets to script "${LIB_NAME}Targets.cmake"
install(
    EXPORT ${LIB_NAME}Targets
    FILE ${LIB_NAME}Targets.cmake
    NAMESPACE Yutils::
    DESTINATION lib/cmake/${LIB_NAME}
)
# Export the targets to script "${LIB_NAME}Targets.cmake"
export(EXPORT ${LIB_NAME}Targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Targets.cmake
    NAMESPACE Yutils::
)