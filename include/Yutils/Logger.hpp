/**
 * @file Logger.hpp
 * @brief A simple logger for C++.
 * @date 2024-04-23; 2024-08-05
 *
 * ## 1. Introduction
 *
 * This is a simple logger for C++ that uses `YLOG_OSTREAM` and `std::format` to
 * print messages to the console.
 *
 * ## 2. Change the log level
 *
 * You can change the log level by defining `YLOG_LEVEL` before including this
 * file.
 *
 * Note that by default, YLOG_LEVEL = 5
 *
 * - YTACE:     YLOG_LEVEL > 4
 * - YINFO:     YLOG_LEVEL > 3
 * - YWARNING:  YLOG_LEVEL > 2
 * - YERROR:    YLOG_LEVEL > 1
 * - YCRITICAL: YLOG_LEVEL > 0
 *
 *
 * ## 3. Change the log format
 *
 * You can also change the log format by defining `_HOW_YTRACE`, `_HOW_YINFO`,
 * `_HOW_YWARNING`, `_HOW_YERROR`, `_HOW_YCRITICAL` before including this file.
 */
#pragma once
#include <format>

#include "Yutils/Color.hpp"
#include "Yutils/Common.hpp"

#ifndef YLOG_LEVEL
    #define YLOG_LEVEL 5
#endif

#define _YLOG_COLOR_RESET YUTILS_COLOR_FUNC_RESET
#define _YLOG_RED YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_RED)
#define _YLOG_GREEN YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_GREEN)
#define _YLOG_YELLOW YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_YELLOW)
#define _YLOG_BLUE YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_BLUE)
#define _YLOG_MAGENTA YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_MAGENTA)
#define _YLOG_CYAN YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_CYAN)
#define _YLOG_WHITE YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_WHITE)

#ifndef YLOG_OSTREAM
    #include <iostream>
    #define YLOG_OSTREAM std::cout
#endif

#define YPRINT(...) YLOG_OSTREAM << std::format(__VA_ARGS__)
#define YFLUSH YLOG_OSTREAM << std::flush

// =============================================================================
// Log Format
// @note You can change the format by defining the following macros before
//       including this file.
// -----------------------------------------------------------------------------
#ifndef _HOW_YTRACE
    #define _HOW_YTRACE                                                        \
        _YLOG_WHITE "{}[{}:{}|{}]: {}" _YLOG_COLOR_RESET "\n", "[TRACE]",      \
            yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YINFO
    #define _HOW_YINFO                                                         \
        _YLOG_GREEN "{}[{}:{}|{}]: {}" _YLOG_COLOR_RESET "\n", "[INFO]",       \
            yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YWARNING
    #define _HOW_YWARNING                                                      \
        _YLOG_YELLOW "{}[{}:{}|{}]: {}" _YLOG_COLOR_RESET "\n", "[WARNING]",   \
            yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YERROR
    #define _HOW_YERROR                                                        \
        _YLOG_RED "{}[{}:{}|{}]: {}" _YLOG_COLOR_RESET "\n", "[ERROR]",        \
            yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YCRITICAL
    #define _HOW_YCRITICAL                                                     \
        _YLOG_MAGENTA "{}[{}:{}|{}]: {}" _YLOG_COLOR_RESET "\n", "[CRITICAL]", \
            yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__
#endif
// =============================================================================

// =============================================================================
// Log Functions
// -----------------------------------------------------------------------------
#if YLOG_LEVEL > 4
    #define YTRACE(...)                                                        \
        YLOG_OSTREAM << std::format(_HOW_YTRACE, std::format(__VA_ARGS__))
#else
    #define YTRACE(...)
#endif

#if YLOG_LEVEL > 3
    #define YINFO(...)                                                         \
        YLOG_OSTREAM << std::format(_HOW_YINFO, std::format(__VA_ARGS__))
#else
    #define YINFO(...)
#endif

#if YLOG_LEVEL > 2
    #define YWARNING(...)                                                      \
        YLOG_OSTREAM << std::format(_HOW_YWARNING, std::format(__VA_ARGS__))
#else
    #define YWARNING(...)
#endif

#if YLOG_LEVEL > 1
    #define YERROR(...)                                                        \
        YLOG_OSTREAM << std::format(_HOW_YERROR, std::format(__VA_ARGS__))
#else
    #define YERROR(...)
#endif

#if YLOG_LEVEL > 0
    #define YCRITICAL(...)                                                     \
        YLOG_OSTREAM << std::format(_HOW_YCRITICAL, std::format(__VA_ARGS__))
#else
    #define YCRITICAL(...)
#endif
// =============================================================================