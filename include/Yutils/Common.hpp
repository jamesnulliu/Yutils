#pragma once

#include <cassert>
#include <cstddef>
#include <string_view>

#include "Yutils/System.hpp"
#include "Yutils/Concepts.hpp"

namespace yutils
{

/**
 * @brief Extract the filename from a path.
 *
 * @param path The path of the file.
 * @return std::string_view
 */
constexpr std::string_view extractFilename(std::string_view path)
{
    for (std::size_t i = path.size() - 1; i >= 0; --i) {
        if (path[i] == '/' || path[i] == '\\') {
            return path.substr(i + 1);
        }
    }
    return path;
}

/**
 * @brief Return the type name of the template parameter.
 *
 * @return constexpr std::string_view
 * @bug [2024/08/03] The first character of the returned string is missing.
 * @bug [2024/09/03] The above bug can be reproduced by both GCC and Clang on
 *                   Windows.
 */
template <typename T>
constexpr std::string_view typeName()
{
#ifdef __clang__
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view kPrefix =
        "std::string_view yutils::type_name() [T = ";
    constexpr std::string_view kSuffix = "]";
#elif defined(__GNUC__)
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view kPrefix =
        "constexpr std::string_view yutils::type_name() [with T = ";
    constexpr std::string_view kSuffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
    std::string_view name = __FUNCSIG__;
    constexpr std::string_view kPrefix =
        "class std::basic_string_view<char,struct std::char_traits<char> "
        "> __cdecl yutils::type_name<";
    constexpr std::string_view kSuffix = ">(void)";
#endif
    name.remove_prefix(kPrefix.size());
    name.remove_suffix(kSuffix.size());
    return name;
}

}  // namespace yutils