#include <future>    // std::future
#include <iostream>  // std::cout

#include <Yutils/ThreadPool.hpp>
#include <spdlog/spdlog.h>

int main()
{
    yutils::bs::ThreadPool pool;
    constexpr double kFirst = 6;
    constexpr double kSecond = 7;
    std::future<double> my_future =
        pool.submit_task([kFirst, kSecond] { return kFirst * kSecond; });
    spdlog::info("The result is: {}", my_future.get());
}