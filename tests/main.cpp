#include "Yutils/ArgParser.hpp"
#include "Yutils/Logger.hpp"
#include "Yutils/Random.hpp"
#include "Yutils/SimpleWriter.hpp"
#include "Yutils/TimeCounter.hpp"

int main(int argc, char* argv[])
{
    yutils::TimeCounter timeCounter;
    timeCounter.init();
    timeCounter.startCounting();

    yutils::ArgParser argParser;
    argParser.addOption("--file", "std::string");
    argParser.addOption("-flag", "ArgParser::flag_t");
    argParser.parse(argc, argv);

    bool flag = argParser.get<bool>("-flag").value_or(false);
    YINFO("Flag: {}", flag);
    auto fileName = argParser.get<std::string>("--file").value_or("");
    YINFO("File name: {}", fileName);

    yutils::RandUniform<int> rand;
    YINFO("{}", rand(0, 100));

    timeCounter.endCounting();
    YTRACE("{}", timeCounter.msecond());

    auto randVec = rand.generateVec(100, 0, 100);
    auto visualizer = yutils::DistributionVisualizer<int>();
    visualizer(randVec, 10, 15);
}