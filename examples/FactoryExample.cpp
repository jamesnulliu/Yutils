#include <cstddef>
#include <future>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include <Yutils/ArgParser.hpp>
#include <Yutils/Factory.hpp>

class CartoonCharacter
{
public:
    explicit CartoonCharacter() = default;
    CartoonCharacter& operator=(const CartoonCharacter&) = delete;
    virtual ~CartoonCharacter() = default;

public:
    virtual void sayHello() const = 0;
};

class YukinoYukinoshita : public CartoonCharacter
{
public:
    explicit YukinoYukinoshita() = default;
    YukinoYukinoshita& operator=(const YukinoYukinoshita&) = delete;
    ~YukinoYukinoshita() override = default;

public:
    void sayHello() const override
    {
        spdlog::info("Hello, I'm Yukino Yukinoshita.");
    }
};

class ShinobuOshino : public CartoonCharacter
{
public:
    explicit ShinobuOshino() = default;
    ShinobuOshino& operator=(const ShinobuOshino&) = delete;
    ~ShinobuOshino() override = default;

public:
    void sayHello() const override
    {
        spdlog::info("Hello, I'm Shinobu Oshino.");
    }
};

/**
 * @brief Creator for Yukino Yukinoshita.
 */
std::shared_ptr<CartoonCharacter> createYukinoYukinoshita()
{
    return std::make_shared<YukinoYukinoshita>();
}

/**
 * @brief Creator for Shinobu Oshino.
 */
std::shared_ptr<CartoonCharacter> createShinobuOshino()
{
    return std::make_shared<ShinobuOshino>();
}

void jobs(std::size_t tid,
          yutils::Factory<std::string,
                          std::function<std::shared_ptr<CartoonCharacter>()>>&
              factory)
{
    spdlog::critical("Thread ID: {}", tid);
    if (tid % 8 == 0) {
        factory.registerCreator("YukinoYukinoshita", createYukinoYukinoshita);
        spdlog::info("Yukino Yukinoshita is registered.");
    } else if (tid % 8 == 1) {
        factory.registerCreator("ShinobuOshino", createShinobuOshino);
        spdlog::info("Shinobu Oshino is registered.");
    } else if (tid % 8 == 2) {
        factory.unregisterCreator("YukinoYukinoshita");
        spdlog::info("Yukino Yukinoshita is unregistered.");
    } else if (tid % 8 == 3) {
        factory.unregisterCreator("ShinobuOshino");
        spdlog::info("Shinobu Oshino is unregistered.");
    } else if (tid % 8 == 4) {
        auto yukino = factory.create("YukinoYukinoshita");
        if (yukino.has_value()) {
            yukino.value()->sayHello();
        } else {
            spdlog::info("Yukino Yukinoshita is not registered.");
        }
    } else if (tid % 8 == 5) {
        auto shinobu = factory.create("ShinobuOshino");
        if (shinobu.has_value()) {
            shinobu.value()->sayHello();
        } else {
            spdlog::info("Shinobu Oshino is not registered.");
        }
    } else if (tid % 8 == 6) {
        auto creator = factory.getCreator("YukinoYukinoshita");
        if (creator) {
            spdlog::info("Creator for Yukino Yukinoshita is found.");
        } else {
            spdlog::info("Creator for Yukino Yukinoshita is not found.");
        }
    } else if (tid % 8 == 7) {
        auto creator = factory.getCreator("ShinobuOshino");
        if (creator) {
            spdlog::info("Creator for Shinobu Oshino is found.");
        } else {
            spdlog::info("Creator for Shinobu Oshino is not found.");
        }
    }
}

int main(int argc, char* argv[])
{

    yutils::ArgParser argParser(argv[0]);
    argParser.addOption("-n", "int", "Number of threads", "8");

    if (!argParser.parse(argc, argv)) {
        argParser.getHelpMessage();
        spdlog::info("\n{}", argParser.getHelpMessage());
        return 0;
    }

    auto numThreads = argParser.get<int>("-n");

    spdlog::set_level(spdlog::level::info);

    yutils::Factory<std::string,
                    std::function<std::shared_ptr<CartoonCharacter>()>>
        factory;

    std::vector<std::future<void>> futures;

    for (std::size_t i = 0; i < numThreads; ++i) {
        futures.push_back(
            std::async(std::launch::async, jobs, i, std::ref(factory)));
    }

    for (auto& future : futures) {
        future.get();
    }

    return 0;
}