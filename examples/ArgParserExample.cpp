#include <Yutils/ArgParser.hpp>
#include <spdlog/spdlog.h>

using namespace yutils;

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("argc: {}", spdlog::fmt_lib::format("{}", argc));

    yutils::ArgParser argParser(argv[0]);

    argParser.addOption("--name", "std::string", "Name of the user", "Tom");
    argParser.addOption("--age", "int", "Age of the user", "18");

    argParser.parse(argc, argv);

    // `ArgParser::get` uses `Serializer::deserialize` to convert the string to
    // the desired type.

    if (argParser.get<bool>("--help")) {
        argParser.getHelpMessage();
        spdlog::trace("\n{}", argParser.getHelpMessage());
        return 0;
    }

    auto name = argParser.get<std::string>("--name");
    auto age = argParser.get<int>("--age");

    spdlog::trace("Name: {}", name);
    spdlog::trace("Age: {}", age);
}