#pragma once
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Yutils/PreDefined.hpp"
#include "Yutils/InnerLogger.hpp"

namespace yutils
{
class ArgParser
{
public:
    YUTILS_API explicit ArgParser() = default;
    YUTILS_API ~ArgParser() = default;

    YUTILS_API void addOption(std::string_view name, std::string_view description,
                              std::string_view type,
                              std::optional<std::string> defaultValue = std::nullopt);
    YUTILS_API bool parse(int argc, char* argv[]) noexcept;

    template <typename T>
    std::optional<T> get(std::string_view name) const
    {
        auto it = m_options.find(name);
        if (it == m_options.end() || !it->second.value) {
            return std::nullopt;
        }
        std::stringstream ss;
        ss << it->second.value.value();
        T value;
        ss >> value;
        if (ss.fail()) {
            _INNER_YWARNING("Failed to convert {} to type {}", it->second.value.value(), it->second.type);
            return std::nullopt;
        }
        return value;
    }

private:
    struct Option
    {
        std::string description;
        std::string type;
        std::optional<std::string> value;
    };
    std::unordered_map<std::string_view, Option> m_options;
};
}  // namespace yutils
