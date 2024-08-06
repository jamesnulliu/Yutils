#include <Yutils/ArgParser.hpp>
#include <Yutils/Logger.hpp>

using namespace yutils;

int main(int argc, char* argv[])
{
    yutils::ArgParser argParser(argv[0]);
    argParser.addOption("--name", "std::string", "Name of the user", "Tom");
    argParser.addOption("--age", "int", "Age of the user", "18");
    argParser.parse(argc, argv);

    // `ArgParser::get` uses `Serializer::deserialize` to convert the string to
    // the desired type.

    if (argParser.get<bool>("--help").value_or(false)) {
        argParser.getHelpMessage();
        YINFO("\n{}", argParser.getHelpMessage());
        return 0;
    }

    auto name = argParser.get<std::string>("--name").value_or("");
    auto age = argParser.get<int>("--age").value_or(0);

    YTRACE("Name: {}", name);
    YTRACE("Age: {}", age);
}