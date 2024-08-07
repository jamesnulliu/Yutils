#pragma once
#include <format>
#include <iostream>

#include "Yutils/Color.hpp"
#include "Yutils/Common.hpp"

#ifndef _INNER_YLOG_LEVEL
    #define _INNER_YLOG_LEVEL 5
#endif

#define _INNER_YLOG_COLOR_RESET "\033[0m"
#define _INNER_YLOG_RED "\033[1;31m"
#define _INNER_YLOG_GREEN "\033[1;32m"
#define _INNER_YLOG_YELLOW "\033[1;33m"
#define _INNER_YLOG_BLUE "\033[1;34m"
#define _INNER_YLOG_MAGENTA "\033[1;35m"
#define _INNER_YLOG_CYAN "\033[1;36m"
#define _INNER_YLOG_WHITE "\033[1;37m"

#define _INNER_YPRINT(...) std::cout << std::format(__VA_ARGS__) << std::endl

#define _INNER_HOW_YTRACE                                                      \
    "{}[{}:{}|{}]: {}\n", "[TRACE]", yutils::extractFilename(__FILE__),        \
        __LINE__, __FUNCTION__

#define _INNER_HOW_YINFO                                                       \
    _INNER_YLOG_GREEN "{}[{}:{}|{}]: {}\n" _INNER_YLOG_COLOR_RESET, "[INFO]",  \
        yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__

#define _INNER_HOW_YWARNING                                                    \
    _INNER_YLOG_YELLOW "{}[{}:{}|{}]: {}\n" _INNER_YLOG_COLOR_RESET,           \
        "[WARNING]", yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__

#define _INNER_HOW_YERROR                                                      \
    _INNER_YLOG_RED "{}[{}:{}|{}]: {}\n" _INNER_YLOG_COLOR_RESET, "[ERROR]",   \
        yutils::extractFilename(__FILE__), __LINE__, __FUNCTION__

#define _INNER_HOW_YCRITICAL                                                   \
    _INNER_YLOG_MAGENTA "{}[{}:{}|{}]: {}\n" _INNER_YLOG_COLOR_RESET,          \
        "[CRITICAL]", yutils::extractFilename(__FILE__), __LINE__,             \
        __FUNCTION__

#if _INNER_YLOG_LEVEL > 4
    #define _INNER_YTRACE(...)                                                 \
        std::cout << std::format(_INNER_HOW_YTRACE, std::format(__VA_ARGS__))
#else
    #define _INNER_YTRACE(...)
#endif

#if _INNER_YLOG_LEVEL > 3
    #define _INNER_YINFO(...)                                                  \
        std::cout << std::format(_INNER_HOW_YINFO, std::format(__VA_ARGS__))
#else
    #define _INNER_YINFO(...)
#endif

#if _INNER_YLOG_LEVEL > 2
    #define _INNER_YWARNING(...)                                               \
        std::cout << std::format(_INNER_HOW_YWARNING, std::format(__VA_ARGS__))
#else
    #define _INNER_YWARNING(...)
#endif

#if _INNER_YLOG_LEVEL > 1
    #define _INNER_YERROR(...)                                                 \
        std::cout << std::format(_INNER_HOW_YERROR, std::format(__VA_ARGS__))
#else
    #define _INNER_YERROR(...)
#endif

#if _INNER_YLOG_LEVEL > 0
    #define _INNER_YCRITICAL(...)                                              \
        std::cout << std::format(_INNER_HOW_YCRITICAL, std::format(__VA_ARGS__))
#else
    #define _INNER_YCRITICAL(...)
#endif