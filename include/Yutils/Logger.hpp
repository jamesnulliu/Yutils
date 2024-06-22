/**
 * @file Logger.hpp
 * @brief A simple logger for C++.
 * @date 2024-04-23
 *
 * # Logger
 *
 * ## 1. Introduction
 *
 * This is a simple logger for C++ that uses `std::cout` and `std::format` to print messages
 * to the console.
 *
 * ## 2. Change the log level
 *
 * You can change the log level by defining `YLOG_LEVEL` before including this file.
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
 * You can also change the log format by defining `_HOW_YTRACE`, `_HOW_YINFO`, `_HOW_YWARNING`,
 * `_HOW_YERROR`, `_HOW_YCRITICAL` before including this file.
 *
 * For example, if you write:
 *
 * ```cpp
 * // main.cpp
 * #define _HOW_YTRACE "{:>10}[{}]: {}\n", "[TRACE]", __FUNCTION__
 * #include "Logger.hpp"
 * int main() { YTRACE("Hello, World!"); }
 * ```
 *
 * Then the output will be:
 * >     [TRACE][main.cpp]: Hello, World!
 */

#pragma once
#include <format>
#include <iostream>
#include <source_location>

namespace yutils
{
constexpr std::string_view _srcFileName(std::string_view s)
{
#if defined(_WIN64) || defined(_WIN32)
    return s.substr(s.find_last_of('\\') + 1);
#else
    return s.substr(s.find_last_of('/') + 1);
#endif  // _WIN64 || _WIN32
}
}  // namespace yutils

#ifndef YLOG_LEVEL
#define YLOG_LEVEL 5
#endif

#define _YLOG_COLOR_RESET "\033[0m"
#define _YLOG_RED "\033[1;31m"
#define _YLOG_GREEN "\033[1;32m"
#define _YLOG_YELLOW "\033[1;33m"
#define _YLOG_BLUE "\033[1;34m"
#define _YLOG_MAGENTA "\033[1;35m"
#define _YLOG_CYAN "\033[1;36m"
#define _YLOG_WHITE "\033[1;37m"

#define YPRINT(...) std::cout << std::format(__VA_ARGS__) << std::endl

// Define the log format >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _HOW_YTRACE
#define _HOW_YTRACE                                                                                \
    "{:>10}[{}:{}|{}]: {}\n", "[TRACE]", yutils::_srcFileName(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YINFO
#define _HOW_YINFO                                                                                 \
    _YLOG_GREEN "{:>10}[{}:{}|{}]: {}\n" _YLOG_COLOR_RESET, "[INFO]",                              \
        yutils::_srcFileName(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YWARNING
#define _HOW_YWARNING                                                                              \
    _YLOG_YELLOW "{:>10}[{}:{}|{}]: {}\n" _YLOG_COLOR_RESET, "[WARNING]",                          \
        yutils::_srcFileName(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YERROR
#define _HOW_YERROR                                                                                \
    _YLOG_RED "{:>10}[{}:{}|{}]: {}\n" _YLOG_COLOR_RESET, "[ERROR]",                               \
        yutils::_srcFileName(__FILE__), __LINE__, __FUNCTION__
#endif

#ifndef _HOW_YCRITICAL
#define _HOW_YCRITICAL                                                                             \
    _YLOG_MAGENTA "{:>10}[{}:{}|{}]: {}\n" _YLOG_COLOR_RESET, "[CRITICAL]",                        \
        yutils::_srcFileName(__FILE__), __LINE__, __FUNCTION__
#endif
// Define the log format <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// Define the log functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if YLOG_LEVEL > 4
#define YTRACE(...) std::cout << std::format(_HOW_YTRACE, std::format(__VA_ARGS__))
#else
#define YTRACE(...)
#endif

#if YLOG_LEVEL > 3
#define YINFO(...) std::cout << std::format(_HOW_YINFO, std::format(__VA_ARGS__))
#else
#define YINFO(...)
#endif

#if YLOG_LEVEL > 2
#define YWARNING(...) std::cout << std::format(_HOW_YWARNING, std::format(__VA_ARGS__))
#else
#define YWARNING(...)
#endif

#if YLOG_LEVEL > 1
#define YERROR(...) std::cout << std::format(_HOW_YERROR, std::format(__VA_ARGS__))
#else
#define YERROR(...)
#endif

#if YLOG_LEVEL > 0
#define YCRITICAL(...) std::cout << std::format(_HOW_YCRITICAL, std::format(__VA_ARGS__))
#else
#define YCRITICAL(...)
#endif
// Define the log functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<