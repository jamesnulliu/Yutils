#include <Yutils/ArgParser.hpp>
#include <Yutils/Random.hpp>
#include <spdlog/spdlog.h>

using namespace yutils;

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("argc: {}", argc);
    for (int i = 0; i < argc; ++i) {spdlog::info("argv[{}]: {}", i, argv[i]);
    }

    yutils::ArgParser argParser(argv[0]);

    // Uniform or normal distribution
    argParser.addOption("--distribution", "std::string",
                        "Distribution of the random number generator; Possible "
                        "value: [uniform, normal]",
                        "uniform");
    argParser.addOption("--dParam1", "double",
                        "Minimum value of the random number", "0");
    argParser.addOption("--dParam2", "double",
                        "Maximum value of the random number", "100");
    argParser.addOption("--num", "size_t",
                        "Number of random numbers to generate", "10");

    if (!argParser.parse(argc, argv)) {
        argParser.getHelpMessage();
        spdlog::critical("\n{}", argParser.getHelpMessage());
        return 0;
    }

    auto distribution = argParser.get<std::string>("--distribution");
    auto dParam1 = argParser.get<double>("--dParam1");
    auto dParam2 = argParser.get<double>("--dParam2");
    auto num = argParser.get<std::size_t>("--num");

    spdlog::trace("Distribution: {}", distribution);
    spdlog::trace("dParam1: {}", dParam1);
    spdlog::trace("dParam2: {}", dParam2);
    spdlog::trace("num: {}", num);

    yutils::RandNormal<double> randNormal;
    yutils::RandUniform<double> randUniform;

    auto genRandNumber = [&]() {
        if (distribution == "uniform") {
            return randUniform.generate(dParam1, dParam2);
        } else if (distribution == "normal") {
            return randNormal.generate(dParam1, dParam2);
        } else {
            throw std::runtime_error("Unknown distribution: " + distribution);
        }
    };

    auto genRandVec = [&](std::size_t num) {
        if (distribution == "uniform") {
            return randUniform.generateVec(num, dParam1, dParam2);
        } else if (distribution == "normal") {
            return randNormal.generateVec(num, dParam1, dParam2);
        } else {
            throw std::runtime_error("Unknown distribution: " + distribution);
        }
    };

    yutils::DistributionVisualizer<double> visualizer;

    auto vec = genRandVec(num);

    visualizer.visualize(genRandVec(num));

    return 0;
}
