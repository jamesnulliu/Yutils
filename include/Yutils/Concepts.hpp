#pragma once

#include <concepts>

namespace yutils
{

template <typename T, typename... Ts>
concept IsAnyOf = (std::is_same_v<T, Ts> || ...);

}  // namespace yutils