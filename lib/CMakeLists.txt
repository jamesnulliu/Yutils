# ==============================================================================
# @file src/CMakeLists.txt
# ==============================================================================

# Library name: "Yutils"
set(TARGET_NAME Yutils)
# Library version
set(TARGET_VERSION ${PROJECT_VERSION})

# Collect all source files
file(GLOB_RECURSE YUTILS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Controlled by ${BUILD_SHARED_LIBS} option
add_library(${TARGET_NAME} ${YUTILS_SRCS})
add_library(Yutils::${TARGET_NAME} ALIAS ${TARGET_NAME})

log_info("Target: ${TARGET_NAME}")

# Set library version
set_target_properties(${TARGET_NAME} PROPERTIES VERSION ${TARGET_VERSION})

# Include directories
target_include_directories(
    ${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Link libraries
target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

target_compile_definitions(${TARGET_NAME} 
    PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:YUTILS_EXPORT>
    INTERFACE $<$<BOOL:${BUILD_SHARED_LIBS}>:YUTILS_IMPORT>
)

# Installations ===============================================================
install_libraries(${TARGET_NAME} Yutils "${TARGET_NAME}")