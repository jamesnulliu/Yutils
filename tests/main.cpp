#include "Yutils/ArgParser.hpp"
#include "Yutils/Logger.hpp"

int main(int argc, char* argv[])
{
    YPRINT("Hello\n");
    yutils::ArgParser argParser;
    argParser.addOption("f", "file", "string", "World.cpp");
    argParser.parse(argc, argv);
    auto val = argParser.get<std::string>("f");
    YCRITICAL("Value: {}\n", *val);
}