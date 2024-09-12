#include <Yutils/ArgParser.hpp>
#include <spdlog/spdlog.h>

using namespace yutils;

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::info);
    spdlog::info("argc: {}", spdlog::fmt_lib::format("{}", argc));

    yutils::ArgParser argParser(argv[0]);

    argParser.addOption("--name", "std::string", "Name of the user", "Tom");
    argParser.addOption("--age", "int", "Age of the user", "18");
    argParser.addOption("-v", "yutils::ArgParser::flag_t", "Verbose mode");

    // `ArgParser::get` uses `Serializer::deserialize` to convert the string to
    // the desired type.
    if (!argParser.parse(argc, argv)) {
        argParser.getHelpMessage();
        spdlog::info("\n{}", argParser.getHelpMessage());
        return 0;
    }

    if (argParser.get<bool>("-v")) {
        spdlog::critical("Verbose mode is on. Setting log level to trace.");
        spdlog::set_level(spdlog::level::trace);
    }

    auto name = argParser.get<std::string>("--name");
    auto age = argParser.get<int>("--age");

    spdlog::trace("Name: {}", name);
    spdlog::trace("Age: {}", age);
    spdlog::info("Name: {}", name);
    spdlog::info("Age: {}", age);
}