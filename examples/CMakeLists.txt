# ==============================================================================
# @file examples/CMakeLists.txt
# ==============================================================================

find_package(spdlog REQUIRED PATHS ${SPDLOG_DIR})
if (NOT spdlog_FOUND)
   log_fatal("spdlog not found")
else()
   log_info("spdlog found")
endif()

link_libraries(Yutils::Yutils)

# ==============================================================================
# ArgParser Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME ArgParserExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
# ==============================================================================

# ==============================================================================
# Serializer Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME SerializerExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
# ==============================================================================

# ==============================================================================
# SimpleCSV Example
# ------------------------------------------------------------------------------
set(EXAMPLE_NAME SimpleCSVExample)
add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
# ==============================================================================