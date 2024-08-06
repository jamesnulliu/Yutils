#pragma once
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include <Yutils/_InnerLogger.hpp>

namespace yutils
{

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
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

    static _ValTy operator()(double min, double max)
    {
        setParams(min, max);
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    static _ValTy operator()()
    {
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    static std::vector<_ValTy> generateVec(std::size_t size, double min,
                                           double max,
                                           const std::string& saveLocation = "")
    {
        std::vector<_ValTy> vec;
        std::uniform_real_distribution<double> distribution(min, max);
        std::ofstream outFile(saveLocation);
        while (size--) {
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
    requires std::is_arithmetic_v<_ValTy>
std::random_device RandUniform<_ValTy>::_rd{};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
thread_local std::default_random_engine RandUniform<_ValTy>::m_engine{_rd()};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
std::shared_ptr<std::uniform_real_distribution<double>>
    RandUniform<_ValTy>::m_distribution{};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
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

    static _ValTy operator()(double mean, double stddev)
    {
        setParams(mean, stddev);
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    static _ValTy operator()()
    {
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    static std::vector<_ValTy> generateVec(std::size_t size, double mean,
                                           double stddev,
                                           const std::string& saveLocation = "")
    {
        std::vector<_ValTy> vec;
        std::normal_distribution<double> distribution(mean, stddev);
        std::ofstream outFile(saveLocation);
        while (size--) {
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
    requires std::is_arithmetic_v<_ValTy>
std::random_device RandNormal<_ValTy>::_rd{};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
thread_local std::default_random_engine RandNormal<_ValTy>::m_engine{_rd()};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
std::shared_ptr<std::normal_distribution<double>>
    RandNormal<_ValTy>::m_distribution{nullptr};

template <class _ValTy>
class DistributionVisualizer
{
public:
    explicit DistributionVisualizer() = default;
    DistributionVisualizer& operator=(const DistributionVisualizer&) = delete;

public:
    static void operator()(const std::vector<_ValTy>& randVec,
                           const std::size_t binNum = 10,
                           const std::size_t maxStarNum = 15)
    {
        _INNER_YWARNING("The type of the elements in the vector is not "
                        "supported by the visualizer.");
    }
};

template <class _ValTy>
    requires std::is_arithmetic_v<_ValTy>
class DistributionVisualizer<_ValTy>
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
    static void operator()(const std::vector<_ValTy>& randVec,
                           const std::size_t binNum = 10,
                           const std::size_t maxStarNum = 15,
                           std::ostream& os = std::cout)
    {
        if (randVec.empty())
            return;
        _ValTy minElem = *(std::min_element(randVec.begin(), randVec.end()));
        _ValTy maxElem = *(std::max_element(randVec.begin(), randVec.end()));
        _ValTy range = maxElem - minElem;

        if (range == 0) {
            os << std::format("All the elements are: {}\n", maxElem);
            return;
        }

        double average = std::accumulate(randVec.begin(), randVec.end(), 0.0) /
                         randVec.size();
        std::vector<std::size_t> bins(binNum);

        os << std::format("Min: {} | Max: {} | Average: {}\n", minElem, maxElem,
                          average);

        for (const auto& val : randVec) {
            std::size_t bin = static_cast<std::size_t>(double(val - minElem) /
                                                       range * binNum);
            if (bin == bins.size()) {
                bin -= 1;
            }
            ++bins[bin];
        }
        std::size_t maxS = *(std::max_element(bins.begin(), bins.end()));
        double resizer = double(maxS) / maxStarNum;
        for (auto& val : bins) {
            val = (std::size_t) ceil(val / resizer);
        }
        for (std::size_t i = 0; i < bins.size(); ++i) {
            os << std::format("{:>3}: ", i);
            for (std::size_t j = 0; j < bins[i]; ++j) {
                os << "*";
            }
            os << "\n";
        }

        os << std::flush;
    }
};

}  // namespace yutils