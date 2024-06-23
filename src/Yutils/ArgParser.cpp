#include "Yutils/ArgParser.hpp"
#include <iostream>

namespace yutils
{
void ArgParser::addOption(std::string optName, std::string type, std::string description,
                          std::optional<std::string> defaultValue)
{
    // Check if the option name is valid.
    if (optName.empty() || !optName.starts_with('-')) {
        _INNER_YWARNING(
            "Skip adding option: Invalid option name: \"{}\"; Option name must start with '-'.",
            optName);
        return;
    }
    // Check if the option already exists.
    if (m_options.find(optName) != m_options.end()) {
        _INNER_YWARNING("Skip adding option: Option \"{}\" already exists.", optName);
        return;
    }
    // If the option is a flag and no default value is provided, set the default value to "false".
    if (type == "ArgParser::flag_t" && defaultValue == std::nullopt) {
        defaultValue = "false";
    }
    // Add the option to the map.
    m_options[optName] = {description, type, defaultValue};
}

bool ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        size_t dashCount = 0;
        auto it = m_options.find(arg);
        if (it != m_options.end()) {
            // Flag option:
            if (it->second.type == "ArgParser::flag_t") {
                // When meeting a flag option, set its value to "true".
                it->second.strVal = "true";
                continue;
            }
            // Value option:
            if (i + 1 < argc) {
                // Here we don't check if `strVal` can be converted to the supposed type.
                // Type check should be done in `ArgParser::construct()`.
                it->second.strVal = argv[i + 1];
                ++i;
            } else {
                _INNER_YERROR("Option \"{}\" requires a value", arg);
                return false;
            }
        } else {
            _INNER_YERROR("Unknown option: \"{}\"", arg);
            return false;
        }
    }
    return true;
}
}  // namespace yutils