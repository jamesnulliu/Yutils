# ==============================================================================
# @file Arguments.cmake
# @brief Global arguments for the whole project.
# ==============================================================================

# Language Standard ------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
log_info("C++ Standard: ${CMAKE_CXX_STANDARD}")

# Build type -------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
log_info("Build Type: ${CMAKE_BUILD_TYPE}")

# Shared or Static Library -----------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared library." OFF)
log_info("Build shared library: ${BUILD_SHARED_LIBS}")

# Build Examples ---------------------------------------------------------------
option(YUTILS_BUILD_EXAMPLES "Whether to build the examples" ON)
log_info("Build Examples: ${YUTILS_BUILD_EXAMPLES}")

# Spdlog install directory -----------------------------------------------------
if(NOT SPDLOG_HOME)
    # Try use environment variable
    if (DEFINED $ENV{SPDLOG_HOME})
        set(SPDLOG_HOME $ENV{SPDLOG_HOME})
    else()
        log_fatal("SPDLOG_HOME is not set.")
    endif()
endif()
log_info("SPDLOG_HOME: ${SPDLOG_HOME}")



