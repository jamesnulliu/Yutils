#include "Yutils/ArgParser.hpp"
#include "Yutils/Logger.hpp"
#include "Yutils/TimeCounter.hpp"
#include "Yutils/Random.hpp"
#include "Yutils/SimpleWriter.hpp"

int main(int argc, char* argv[])
{
    yutils::TimeCounter timeCounter;
    timeCounter.init();
    timeCounter.startCounting();

    yutils::SimpleWriter writer("test.csv", 3);
    writer.addRow("Hello", "World", "!");
    writer.addRow("1", "2", "3");
    writer.addRow("You", "are", "awesome");

    YPRINT("Hello");

    yutils::ArgParser argParser;
    argParser.addOption("f", "file", "string", "World.cpp");
    argParser.parse(argc, argv);
    auto val = argParser.get<std::string>("f");
    YCRITICAL("Value: {}", *val);

    yutils::RandUniform<int> rand;
    YINFO("{}", rand(0, 100));

    timeCounter.endCounting();
    YTRACE("{}", timeCounter.msecond());
}