#pragma once
#include <algorithm>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <type_traits>
#include <vector>

namespace yutils
{

template <class _ValTy>
class RandUniform
{
public:
    explicit RandUniform() = default;
    RandUniform& operator()(const RandUniform&) = delete;

public:
    static void setParams(double min, double max)
    {
        if (m_distribution == nullptr || m_distribution->min() != min ||
            m_distribution->max() != max) {
            m_distribution =
                std::make_shared<std::uniform_real_distribution<double>>(min,
                                                                         max);
        }
    }

    _ValTy operator()(double min, double max)
    {
        setParams(min, max);
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    _ValTy operator()()
    {
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    std::vector<_ValTy> generateVec(std::size_t size, double min, double max,
                                    const std::string& saveLocation = "")
    {
        std::vector<_ValTy> vec;
        std::uniform_real_distribution<double> distribution(min, max);
        std::ofstream outFile(saveLocation);
        while ((size--) != 0u) {
            vec.push_back((_ValTy) distribution(m_engine));
            if (outFile.is_open()) {
                outFile << vec.back() << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::shared_ptr<std::uniform_real_distribution<double>>
        m_distribution;
};

template <class _ValTy>
std::random_device RandUniform<_ValTy>::_rd{};

template <class _ValTy>
thread_local std::default_random_engine RandUniform<_ValTy>::m_engine{_rd()};

template <class _ValTy>
std::shared_ptr<std::uniform_real_distribution<double>>
    RandUniform<_ValTy>::m_distribution{};

template <class _ValTy>
class RandNormal
{
public:
    explicit RandNormal() = default;
    RandNormal& operator()(const RandNormal&) = delete;

public:
    static void setParams(double mean, double stddev)
    {
        if (m_distribution == nullptr || m_distribution->mean() != mean ||
            m_distribution->stddev() != stddev) {
            m_distribution = std::make_shared<std::normal_distribution<double>>(
                mean, stddev);
        }
    }

    _ValTy operator()(double mean, double stddev)
    {
        setParams(mean, stddev);
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    _ValTy operator()()
    {
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    std::vector<_ValTy> generateVec(std::size_t size, double mean,
                                    double stddev,
                                    const std::string& saveLocation = "")
    {
        std::vector<_ValTy> vec;
        std::normal_distribution<double> distribution(mean, stddev);
        std::ofstream outFile(saveLocation);
        while ((size--) != 0u) {
            vec.push_back(_ValTy(distribution(m_engine)));
            if (outFile.is_open()) {
                outFile << vec.back() << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::shared_ptr<std::normal_distribution<double>> m_distribution;
};

template <class _ValTy>
std::random_device RandNormal<_ValTy>::_rd{};

template <class _ValTy>
thread_local std::default_random_engine RandNormal<_ValTy>::m_engine{_rd()};

template <class _ValTy>
std::shared_ptr<std::normal_distribution<double>>
    RandNormal<_ValTy>::m_distribution{nullptr};

template <class _ValTy>
class DistributionVisualizer
{
public:
    explicit DistributionVisualizer() = default;
    DistributionVisualizer& operator=(const DistributionVisualizer&) = delete;

public:
    /**
     * @brief Visualizes the distribution of a vector of random numbers.
     *
     * @param randVec The vector of random numbers.
     * @param binNum The number of bins to divide the range of the random
     * numbers.
     * @param maxStarNum The maximum number of stars to print in each bin.
     */
    void operator()(const std::vector<_ValTy>& randVec,
                    const std::size_t kBinNum = 10,
                    const std::size_t kMaxStarNum = 15,
                    std::ostream& os = std::cout)
    {

        m_logger->critical("I am here!!");
        if constexpr (!std::is_arithmetic_v<_ValTy>) {
            m_logger->warn("The type of the elements in the vector is not "
                           "supported by the visualizer.");
        } else {
            if (randVec.empty()) {
                return;
            }
            _ValTy minElem =
                *(std::min_element(randVec.begin(), randVec.end()));
            _ValTy maxElem =
                *(std::max_element(randVec.begin(), randVec.end()));
            _ValTy range = maxElem - minElem;

            if (range == 0) {
                os << spdlog::fmt_lib::format("All the elements are: {}\n",
                                              maxElem);
                return;
            }

            m_logger->info("Min: {} | Max: {}", minElem, maxElem);

            double average =
                std::accumulate(randVec.begin(), randVec.end(), 0.0) /
                randVec.size();
            std::vector<std::size_t> bins(kBinNum);

            os << spdlog::fmt_lib::format("Min: {} | Max: {} | Average: {}\n",
                                          minElem, maxElem, average);

            for (const auto& val : randVec) {
                auto bin = static_cast<std::size_t>(double(val - minElem) /
                                                    range * kBinNum);
                if (bin == bins.size()) {
                    bin -= 1;
                }
                ++bins[bin];
            }
            std::size_t maxS = *(std::max_element(bins.begin(), bins.end()));
            double resizer = double(maxS) / kMaxStarNum;
            for (auto& val : bins) {
                val = (std::size_t) ceil(val / resizer);
            }
            for (std::size_t i = 0; i < bins.size(); ++i) {
                os << spdlog::fmt_lib::format("{:>3}: ", i);
                for (std::size_t j = 0; j < bins[i]; ++j) {
                    os << "*";
                }
                os << "\n";
            }

            os << std::flush;
        }
    }

private:
    std::shared_ptr<spdlog::logger> m_logger =
        spdlog::stdout_color_mt("yutils::DistributionVisualizer");
};

}  // namespace yutils