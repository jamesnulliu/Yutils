#pragma once
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Yutils/Serializer.hpp"
#include "Yutils/System.hpp"

namespace yutils
{
class ArgParser
{
public:
    using flag_t = bool;

public:
    YUTILS_API explicit ArgParser(std::string_view argv0);
    ~ArgParser() = default;

public:
    /**
     * @brief Add an option to the parser (store the option in the parser's
     *        internal map). If the option already exists, it will be skipped.
     *
     * @param optName The name (key) of the option.
     * @param supposedType The supposed type of the option.
     *        [Note]:
     *        1. This is just a suggestion for the option's type; The actual
     *           type is determined when calling `ArgParser::get()`. There will
     *           be no type check about whether `defaultValue` can be converted
     *           to `supposedType` in this function.
     *        2. If provided `ArgParser::flag_t` for `supposedType`, the option
     *           is supposed to be a flag (which doesn't require a value); When
     *           parsing, if the option is found, its value will be set to
     *           `true`; Otherwise, it will be set to `false`.
     * @param description [Optional] The description of the option.
     * @param defaultValue [Optional] The default value of the option.
     */
    YUTILS_API void addOption(
        const std::string& optName, const std::string& supposedType,
        const std::string& description = "",
        std::optional<std::string> defaultValue = std::nullopt);

    YUTILS_API bool parse(int argc, char* argv[]) noexcept;

    /**
     * @brief Get the value of the option with the specified name.
     *        `Serializer<std::string>::deserialize` is used to convert the
     *        string value to the desired type.
     *
     * @tparam T The type of the option.
     * @param optName The name of the option.
     */
    template <typename T>
    T get(std::string optName) const
    {
        auto it = m_options.find(optName);
        // Throw an exception if the option is not added.
        // User should not `get` an option before adding it with `addOption`.
        if (it == m_options.end()) {
            spdlog::error("Option \"{}\" not added. Call "
                          "`ArgParser::addOption` before getting the value.",
                          optName);
            throw std::runtime_error("Option not added.");
        }
        // Return `std::nullopt` if the option is not parsed and no default
        // value provided.
        if (it->second.strVal == std::nullopt) {
            spdlog::error(
                "Option \"{}\" not parsed and no default value provided.",
                optName);
            throw std::runtime_error("Option not parsed.");
        }
        // Deserialize the string value to the supposed type.
        // This function may throw a runtime error if the conversion fails.
        return Serializer<std::string>::deserialize<T>(
            it->second.strVal.value());
    }

    std::string getHelpMessage() const
    {
        return m_helpMessage;
    }

private:
    struct Option
    {
        std::string description;  // Description of the option.
        std::string type;         // Supposed type of the option.
        std::optional<std::string> strVal;
    };
    std::unordered_map<std::string, Option> m_options;
    std::string m_helpMessage;
};
}  // namespace yutils
