#include <cstddef>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <spdlog/spdlog.h>

#include <Yutils/Factory.hpp>
#include <Yutils/TypeTraits.hpp>

yutils::Registry<false, std::string, std::function<void()>> helloFnRegistry;

class CartoonCharacter
{
public:
    explicit CartoonCharacter() = default; CartoonCharacter& operator=(const CartoonCharacter&) = delete;
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
        // spdlog::info("Hello, I'm Yukino Yukinoshita.");
        helloFnRegistry.get(
            std::string{yutils::type_traits::typeName<YukinoYukinoshita>()})();
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
        // spdlog::info("Hello, I'm Shinobu Oshino.");
        helloFnRegistry.get(
            std::string{yutils::type_traits::typeName<ShinobuOshino>()})();
    }
};

int main(int argc, char* argv[])
{

    spdlog::set_level(spdlog::level::info);

    std::string typenameYukino{
        yutils::type_traits::typeName<YukinoYukinoshita>()};
    std::string typenameShinobu{yutils::type_traits::typeName<ShinobuOshino>()};

    helloFnRegistry.add(typenameYukino, [&]() {
        spdlog::info(spdlog::fmt_lib::format("Hello from {}.", typenameYukino));
    });
    helloFnRegistry.add(typenameShinobu, [&]() {
        spdlog::info(
            spdlog::fmt_lib::format("Hello from {}.", typenameShinobu));
    });

    yutils::Factory<false, std::string> factory;
    factory.add<YukinoYukinoshita>("YukinoYukinoshita");
    factory.add<ShinobuOshino>("ShinobuOshino");
    auto yukino = factory.create<CartoonCharacter>("YukinoYukinoshita");
    yukino->sayHello();
    auto shinobu = std::static_pointer_cast<CartoonCharacter>(
        factory.create("ShinobuOshino"));
    shinobu->sayHello();

    return 0;
}
