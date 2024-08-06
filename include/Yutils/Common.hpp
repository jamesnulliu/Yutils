#pragma once

#include "Yutils/System.hpp"
#include <cassert>
#include <string_view>


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
 */
template <typename T>
constexpr std::string_view typeName()
{
#ifdef __clang__
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view prefix =
        "std::string_view yutils::type_name() [T = ";
    constexpr std::string_view suffix = "]";
#elif defined(__GNUC__)
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view prefix =
        "constexpr std::string_view yutils::type_name() [with T = ";
    constexpr std::string_view suffix = "]";
#elif defined(_MSC_VER)
    std::string_view name = __FUNCSIG__;
    constexpr std::string_view prefix =
        "class std::basic_string_view<char,struct std::char_traits<char> "
        "> __cdecl yutils::type_name<";
    constexpr std::string_view suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

}  // namespace yutils