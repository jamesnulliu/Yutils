#include <iostream>
#include "Yutils/ArgParser.hpp"

namespace yutils
{
void ArgParser::addOption(std::string_view name, std::string_view description,
                          std::string_view type, std::optional<std::string> defaultValue)
{
    if (m_options.find(name) != m_options.end()) {
        _INNER_YERROR("Option \"{}\" already exists", name);
        return;
    }
    if (type != "string" && type != "int" && type != "float" && type != "bool") {
        _INNER_YERROR("Invalid type: \"{}\"; Supported types are: string, int, float, bool", type);
        return;
    }
    if (defaultValue && type != "string") {
        if (type == "int") {
            try {
                std::stoi(defaultValue.value());
            } catch (const std::invalid_argument& e) {
                _INNER_YERROR("Invalid default value for option \"{}\"; Expected type: int", name);
                return;
            }
        } else if (type == "float") {
            try {
                std::stof(defaultValue.value());
            } catch (const std::invalid_argument& e) {
                _INNER_YERROR("Invalid default value for option \"{}\"; Expected type: float", name);
                return;
            }
        } else if (type == "bool") {
            if (defaultValue.value() != "true" && defaultValue.value() != "false") {
                _INNER_YERROR("Invalid default value for option \"{}\"; Expected type: bool", name);
                return;
            }
        }
    }
    m_options[name] = {std::string(description), std::string(type), defaultValue};
}

bool ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        size_t dashCount = 0;
        if (arg.starts_with("--")) {
            dashCount = 2;
        } else if (arg.starts_with("-")) {
            dashCount = 1;
        } else {
            _INNER_YERROR("Invalid argument: \"{}\"; "
                        "An argument must starts with \"-\" or \"--\"",
                        arg);
            return false;
        }
        arg.remove_prefix(dashCount);
        auto it = m_options.find(arg);
        if (it != m_options.end()) {
            if (i + 1 < argc) {
                it->second.value = argv[i + 1];
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