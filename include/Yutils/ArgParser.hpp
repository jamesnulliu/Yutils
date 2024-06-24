#pragma once
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Yutils/InnerLogger.hpp"
#include "Yutils/PreDefined.hpp"

namespace yutils
{
template <typename T>
inline std::optional<T> convertStrArg(std::string strVal, std::string type)
{
    if (strVal == "") {
        return T{};
    }
    std::stringstream ss(strVal);
    T value;
    ss >> value;
    if (ss.fail()) {
        _INNER_YWARNING("Failed converting value {} to type {}; Supposed type: {}", strVal,
                        typeid(T).name(), type);
        return std::nullopt;
    }
    return value;
}

template <>
inline std::optional<std::string> convertStrArg(std::string strVal, std::string type)
{
    return strVal;
}

template <>
inline std::optional<bool> convertStrArg(std::string strVal, std::string type)
{
    if (strVal == "false") {
        return false;
    }
    return true;
}

class ArgParser
{
public:
    using flag_t = bool;

public:
    explicit ArgParser() = default;
    ~ArgParser() = default;

public:
    /**
     * @brief Add an option to the parser (store the option in the parser's internal map).
     *        If the option already exists, it will be skipped.
     *
     * @param optName The name of the option.
     * @param type [Optional] The supposed type of the option.
     *             1. Note that this is just an suggestion for the option's type; The actual type
     *             is determined when calling `ArgParser::get()`. There will be no type check about
     *             whether `defaultValue` can be converted to `type` in this function.
     *             2. If provided `ArgParser::flag_t` for `type`, the option is supposed to be a
     *             flag (which doesn't require a value); If no default value is provided to a flag
     *             option, the default value will be set to `false`.
     * @param description [Optional] The description of the option.
     * @param defaultValue [Optional] The default value of the option.
     */
    YUTILS_API void addOption(std::string optName, std::string type, std::string description = "",
                              std::optional<std::string> defaultValue = std::nullopt);

    YUTILS_API bool parse(int argc, char* argv[]) noexcept;

    template <typename T>
    std::optional<T> get(std::string optName) const
    {
        auto it = m_options.find(optName);
        if (it == m_options.end()) {
            _INNER_YWARNING("Option \"{}\" not added.", optName);
            return std::nullopt;
        }
        if (it->second.strVal == std::nullopt) {
            _INNER_YERROR("Option \"{}\" not parsed.", optName);
            throw std::runtime_error("Option not parsed.");
            return std::nullopt;
        }
        return convertStrArg<T>(it->second.strVal.value(), it->second.type);
    }

private:
    struct Option
    {
        std::string description;            // Description of the option.
        std::string type;                   // Supposed type of the option.
        std::optional<std::string> strVal;  // The value of the option in string format.
    };
    std::unordered_map<std::string, Option> m_options;
};

}  // namespace yutils
