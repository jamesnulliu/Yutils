#pragma once

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

}  // namespace yutils::type_traits