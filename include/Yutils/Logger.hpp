#pragma once
#include <format>
#include <iostream>
#include <source_location>

namespace yutils
{
    constexpr std::string_view _sourceFileName(std::string_view s)
    {
#if defined(_WIN64) || defined(_WIN32)
        return s.substr(s.find_last_of('\\') + 1);
#else
        return s.substr(s.find_last_of('/') + 1);
#endif // _WIN64 || _WIN32
    }
} // namespace yutils

#define _YUTILS_LOG_COLOR_RESET "\033[0m"
#define _YUTILS_LOG_RED "\033[1;31m"
#define _YUTILS_LOG_GREEN "\033[1;32m"
#define _YUTILS_LOG_YELLOW "\033[1;33m"
#define _YUTILS_LOG_BLUE "\033[1;34m"
#define _YUTILS_LOG_MAGENTA "\033[1;35m"
#define _YUTILS_LOG_CYAN "\033[1;36m"
#define _YUTILS_LOG_WHITE "\033[1;37m"

#define _YUTILS_LOG_FMT "[{}:{}|{}] >>> {}\n"

#define YPRINT(...) std::cout << std::format(__VA_ARGS__)

#define YTRACE(...)                                                                        \
    std::cout << std::format(_YUTILS_LOG_FMT, yutils::_sourceFileName(__FILE__), __LINE__, \
                             __FUNCTION__, std::format(__VA_ARGS__))

#define YINFO(...)                                                                      \
    std::cout << std::format(_YUTILS_LOG_GREEN _YUTILS_LOG_FMT _YUTILS_LOG_COLOR_RESET, \
                             yutils::_sourceFileName(__FILE__), __LINE__, __FUNCTION__, \
                             std::format(__VA_ARGS__))

#define YWARNING(...)                                                                    \
    std::cout << std::format(_YUTILS_LOG_YELLOW _YUTILS_LOG_FMT _YUTILS_LOG_COLOR_RESET, \
                             yutils::_sourceFileName(__FILE__), __LINE__, __FUNCTION__,  \
                             std::format(__VA_ARGS__))

#define YERROR(...)                                                                     \
    std::cout << std::format(_YUTILS_LOG_RED _YUTILS_LOG_FMT _YUTILS_LOG_COLOR_RESET,   \
                             yutils::_sourceFileName(__FILE__), __LINE__, __FUNCTION__, \
                             std::format(__VA_ARGS__))

#define YCRITICAL(...)                                                                  \
    std::cout << std::format(_YUTILS_LOG_CYAN _YUTILS_LOG_FMT _YUTILS_LOG_COLOR_RESET,  \
                             yutils::_sourceFileName(__FILE__), __LINE__, __FUNCTION__, \
                             std::format(__VA_ARGS__))
