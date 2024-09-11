#pragma once

#include <string_view>

namespace yutils::type_traits
{

template <typename>
struct GetInnerType;

template <template <typename...> class TemplateClass, typename InnerType>
struct GetInnerType<TemplateClass<InnerType>>
{
    using type = InnerType;
};

template <typename T>
using GetInnerType_t = typename GetInnerType<T>::type;

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
#if defined(__clang__)
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view kPrefix =
        "std::string_view yutils::type_traits::typeName() [T = ";
    constexpr std::string_view kSuffix = "]";
#elif defined(__GNUC__)
    std::string_view name = __PRETTY_FUNCTION__;
    constexpr std::string_view kPrefix =
        "constexpr std::string_view yutils::type_traits::typeName() [with T = ";
    constexpr std::string_view kSuffix =
        "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
    std::string_view name = __FUNCSIG__;
    constexpr std::string_view kPrefix =
        "class std::basic_string_view<char,struct std::char_traits<char> "
        "> __cdecl yutils::type_traits::typeName<";
    constexpr std::string_view kSuffix = ">(void)";
#else
    #error "Unsupported compiler."
#endif
    name.remove_prefix(kPrefix.size());
    name.remove_suffix(kSuffix.size());
    return name;
}

}  // namespace yutils::type_traits