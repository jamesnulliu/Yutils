#include <type_traits>
#include <utility>

#include "Yutils/System.hpp"

namespace yutils
{

template <typename T, typename = void>
struct IsRange : std::false_type
{
};

template <typename T>
struct IsRange<T, std::void_t<decltype(std::begin(std::declval<T>())),
                              decltype(std::end(std::declval<T>()))>> : std::true_type
{};

}  // namespace yutils
