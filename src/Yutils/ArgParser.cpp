#include <memory>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "Yutils/ArgParser.hpp"
#include "Yutils/Common.hpp"

namespace yutils
{
ArgParser::ArgParser(std::string_view argv0)
{
    m_logger = spdlog::stdout_color_mt("yutils::ArgParser");

    m_helpMessage =spdlog::fmt_lib::format("Usage:\n    {} [options...]\nOptions:\n",yutils::extractFilename(argv0));

    // Add the executable name to the help message.
    m_options["--help"] = {"Show help messages.", "yutils::Argparser::flag_t", "false"};

    m_helpMessage +=
        generateHelpMessage("--help", m_options["--help"]);
};

void ArgParser::addOption(const std::string& optName, const std::string& type,
                          const std::string& description,
                          std::optional<std::string> defaultValue)
{
    using spdlog::fmt_lib::format;
    if (optName == "--help") {
        m_logger->warn("Skip adding option: Option name \"--help\" is "
                       "reserved for help message.");
        return;
    }

    // Check if the option name is valid.
    if (optName.empty() || !(optName.substr(0, 1) == "-")) {
        m_logger->warn("Skip adding option: Invalid option name: {}; "
                       "Option name must start with '-'.",
                       optName);
        return;
    }

    // Check if the option already exists.
    if (m_options.find(std::string(optName)) != m_options.end()) {
        m_logger->warn("Skip adding option: Option {} already exists.",
                       optName);
        return;
    }

    // IF: The type is `yutils::ArgParser::flag_t`, set the default value to
    //     `false`.
    if (type == "yutils::ArgParser::flag_t") {
        defaultValue = "false";
    }

    // Add the option to the map.
    m_options[optName] = {description, type, defaultValue};

    m_helpMessage += generateHelpMessage(optName, m_options[optName]);
}

bool ArgParser::parse(int argc, char* argv[]) noexcept
{
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto it = m_options.find(arg);

        // IF: Unknown option, stop parsing and return false:
        if (it == m_options.end()) {
            m_logger->error("Unknown option: \"{}\"", arg);
            return false;
        }

        // IF: Help option, stop parsing and return false:
        if (arg == "--help") {
            m_options["--help"].strVal = "true";
            return false;
        }

        // IF: flag option:
        if (it->second.type == "yutils::ArgParser::flag_t") {
            // Flag options don't require a value. Set the value to `true`.
            it->second.strVal = "true";
            continue;
        }

        // IF: value option:
        if (i + 1 < argc) {
            // [note]: Here we don't check if `strVal` can be converted to the
            //         supposed type.
            it->second.strVal = argv[i + 1];
            ++i;
        } else {
            m_logger->error("Option \"{}\" requires a value", arg);
            return false;
        }
    }

    return true;
}
std::string ArgParser::generateHelpMessage(std::string_view arg,
                                           const Option& option) const
{
    auto [description, type, strVal] = option;
    if (option.type != "yutils::ArgParser::flag_t") {
        type += " <value>";
    }
    return spdlog::fmt_lib::format("  Arg: {}\n  |- Type: {}\n  |- Default: "
                                   "{}\n  |- Description: {}\n",
                                   arg, type, strVal.value_or(""), description);
}
}  // namespace yutils
