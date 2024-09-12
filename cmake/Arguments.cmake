# ==============================================================================
# @file Arguments.cmake
# @brief Global arguments for the whole project.
# ==============================================================================

yutils_log_info("Setting up arguments...")

# Language Standard ------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
yutils_log_info("|- C++ Standard: ${CMAKE_CXX_STANDARD}")

# Build type -------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
yutils_log_info("|- Build Type: ${CMAKE_BUILD_TYPE}")

# Shared or Static Library -----------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared library." OFF)
yutils_log_info("|- Build shared library: ${BUILD_SHARED_LIBS}")

# Build Examples ---------------------------------------------------------------
option(YUTILS_BUILD_EXAMPLES "Whether to build the examples" ON)
yutils_log_info("|- Build Examples: ${YUTILS_BUILD_EXAMPLES}")

# Spdlog install directory -----------------------------------------------------
if(NOT SPDLOG_HOME)
    # Try use environment variable
    if (NOT $ENV{SPDLOG_HOME} STREQUAL "")
        set(SPDLOG_HOME $ENV{SPDLOG_HOME})
    else()
        yutils_log_fatal("|- SPDLOG_HOME is not set.")
    endif()
endif()
yutils_log_info("|- SPDLOG_HOME: ${SPDLOG_HOME}")



