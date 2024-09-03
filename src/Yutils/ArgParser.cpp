#include "Yutils/ArgParser.hpp"
#include "Yutils/Common.hpp"
#include <format>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

namespace yutils
{
ArgParser::ArgParser(std::string_view argv0)
{
    m_options["--help"] = {"Show help messages.", "flag_t", "false"};
    m_helpMessage = std::format("Usage:\n    {} [options]\nOptions:\n",
                                extractFilename(argv0));
    m_helpMessage += std::format("  {:<20} {:<20} {:<20} \"{}\"\n", "--help",
                                 "flag_t", "[false]", "Show help messages.");
};

void ArgParser::addOption(const std::string& optName, const std::string& type,
                          const std::string& description,
                          std::optional<std::string> defaultValue)
{
    if (optName == "--help") {
        spdlog::warn("Skip adding option: Option name \"--help\" is "
                     "reserved for help message.");
        return;
    }
    // Check if the option name is valid.
    if (optName.empty() || !optName.starts_with('-')) {
        spdlog::warn("Skip adding option: Invalid option name: \"{}\"; "
                     "Option name must start with '-'.",
                     optName);
        return;
    }
    // Check if the option already exists.
    if (m_options.find(std::string(optName)) != m_options.end()) {
        spdlog::warn("Skip adding option: Option \"{}\" already exists.",
                     optName);
        return;
    }
    if (type == "ArgParser::flag_t") {
        defaultValue = "false";
        m_helpMessage += spdlog::fmt_lib::format(
            "  {:<20} {:<20} {:<20} \"{}\"\n", optName, type,
            spdlog::fmt_lib::format("[{}]", defaultValue.value_or("")),
            description);
    } else {
        m_helpMessage += spdlog::fmt_lib::format(
            "  {:<20} {:<20} {:<20} \"{}\"\n", optName + " <value>", type,
            spdlog::fmt_lib::format("[{}]", defaultValue.value_or("")),
            description);
    }
    // Add the option to the map.
    m_options[optName] = {description, type, defaultValue};
}

bool ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto it = m_options.find(arg);
        if (it != m_options.end()) {
            if (arg == "--help") {
                m_options["--help"].strVal = "true";
                break;
            }
            // If flag option:
            if (it->second.type == "ArgParser::flag_t") {
                // When meeting a flag option, set its value to "true".
                it->second.strVal = "true";
                continue;
            }
            // If value option:
            if (i + 1 < argc) {
                // Here we don't check if `strVal` can be converted to the
                // supposed type. Type check should be done in
                // `ArgParser::construct()`.
                it->second.strVal = argv[i + 1];
                ++i;
            } else {
                spdlog::error("Option \"{}\" requires a value", arg);
                return false;
            }
        } else {
            spdlog::error("Unknown option: \"{}\"", arg);
            return false;
        }
    }

    return true;
}
}  // namespace yutils