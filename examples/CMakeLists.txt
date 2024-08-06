# ==============================================================================
# @file examples/CMakeLists.txt
# ==============================================================================

include_directories(${PROJECT_SOURCE_DIR}/include)
link_libraries(Yutils)

set(
    EXAMPLE_EXE_OUT_DIR
    ${OUTPUT_DIR}/bin/examples/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}
)

# ==============================================================================
# ArgParser Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME ArgParserExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${EXAMPLE_NAME} PRIVATE YUTILS_IMPORT)
endif()
set_target_properties(
    ${EXAMPLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE_EXE_OUT_DIR}
)
# ==============================================================================

# ==============================================================================
# Serializer Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME SerializerExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${EXAMPLE_NAME} PRIVATE YUTILS_IMPORT)
endif()
set_target_properties(
    ${EXAMPLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE_EXE_OUT_DIR}
)
# ==============================================================================

# ==============================================================================
# SimpleCSV Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME SimpleCSVExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${EXAMPLE_NAME} PRIVATE YUTILS_IMPORT)
endif()
set_target_properties(
    ${EXAMPLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE_EXE_OUT_DIR}
)
# ==============================================================================

# ==============================================================================
# Logger Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME LoggerExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
if (BUILD_SHARED_LIBS)
    target_compile_definitions(${EXAMPLE_NAME} PRIVATE YUTILS_IMPORT)
endif()
set_target_properties(
    ${EXAMPLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE_EXE_OUT_DIR}
)
# ==============================================================================

