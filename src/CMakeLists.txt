# ==============================================================================
# @file src/CMakeLists.txt
# ==============================================================================

# Library name: "Yutils"
set(TARGET_NAME Yutils)
# Library version
set(TARGET_VERSION ${PROJECT_VERSION})

find_package(spdlog REQUIRED PATHS ${SPDLOG_HOME})

# Collect all source files
file(GLOB_RECURSE YUTILS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Controlled by ${BUILD_SHARED_LIBS} option
add_library(${TARGET_NAME} ${YUTILS_SRCS})
add_library(Yutils::${TARGET_NAME} ALIAS ${TARGET_NAME})

log_info("${CYAN_CAT} Target: ${TARGET_NAME}")

# Set library version
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${TARGET_VERSION})

# Include directories
target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Build Type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE DEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${TARGET_NAME} PRIVATE RELEASE_BUILD)
else()
    log_fatal("Unsupported Build Type: ${CMAKE_BUILD_TYPE}")
endif()

if(BUILD_SHARED_LIBS)  # Shared Library
    target_compile_definitions(${TARGET_NAME} PRIVATE YUTILS_EXPORT)
    target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
    target_compile_definitions(${TARGET_NAME} INTERFACE YUTILS_IMPORT)
else()  # Static Library
    target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)
endif()

# Installations ===============================================================
install_libraries(${TARGET_NAME} Yutils "${TARGET_NAME}")