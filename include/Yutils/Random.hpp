#pragma once
#include "Yutils/Concepts.hpp"
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
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
    inline _ValTy operator()(double min, double max) const
    {
        if (m_distribution == nullptr || m_distribution->min() != min ||
            m_distribution->max() != max) {
            m_distribution = new std::uniform_real_distribution<double>(min, max);
        }
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    inline _ValTy operator()() const
    {
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    inline void setParams(double min, double max) const
    {
        if (m_distribution == nullptr || m_distribution->min() != min ||
            m_distribution->max() != max) {
            m_distribution = new std::uniform_real_distribution<double>(min, max);
        }
    }

    std::vector<_ValTy> generateVec(size_t size, double min, double max,
                                    const std::string& saveLocation = "") const
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
    static std::uniform_real_distribution<double>* m_distribution;
};

template <class _ValTy>
std::random_device RandUniform<_ValTy>::_rd{};

template <class _ValTy>
thread_local std::default_random_engine RandUniform<_ValTy>::m_engine{_rd()};

template <class _ValTy>
std::uniform_real_distribution<double>* RandUniform<_ValTy>::m_distribution{nullptr};

template <class _ValTy>
class RandNormal
{
public:
    inline _ValTy operator()(double mean, double stddev) const
    {
        if (m_distribution == nullptr || m_distribution->mean() != mean ||
            m_distribution->stddev() != stddev) {
            m_distribution = new std::normal_distribution<double>(mean, stddev);
        }
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    std::vector<_ValTy> generateVec(size_t size, double mean, double stddev,
                                    const std::string& saveLocation = "") const
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
    static std::normal_distribution<double>* m_distribution;
};

template <class _ValTy>
std::random_device RandNormal<_ValTy>::_rd{};

template <class _ValTy>
thread_local std::default_random_engine RandNormal<_ValTy>::m_engine{_rd()};

template <class _ValTy>
std::normal_distribution<double>* RandNormal<_ValTy>::m_distribution{nullptr};

template<class _ValTy>
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
     * @param binNum The number of bins to divide the range of the random numbers.
     * @param maxStarNum The maximum number of stars to print in each bin.
     */
    void operator()(
        const std::vector<_ValTy>& randVec,
        const size_t binNum = 10,
        const size_t maxStarNum = 15
        ) const
    {
        if (randVec.empty()) return;
        _ValTy minElem = *(std::min_element(randVec.begin(), randVec.end()));
        _ValTy maxElem = *(std::max_element(randVec.begin(), randVec.end()));
        _ValTy range = maxElem - minElem;

        if (range == 0) {
            std::cout << "All the elements are: " << maxElem << std::endl;
            return;
        }

        double average = std::accumulate(randVec.begin(), randVec.end(), 0.0) / randVec.size();
        std::vector<size_t> bins(binNum);

        std::cout << "min: " << minElem << " max: " << maxElem << " average: " << average << std::endl;

        for (const auto& val : randVec) {
            size_t bin = static_cast<size_t>(double(val - minElem) / range * binNum);
            if (bin == bins.size()) { bin -= 1; }
            ++bins[bin];
        }
        size_t maxS = *(std::max_element(bins.begin(), bins.end()));
        double resizer = double(maxS) / maxStarNum;
        for (auto& val : bins) {
            val = (size_t)ceil(val / resizer);
        }
        for (size_t i = 0; i < bins.size(); ++i) {
            std::cout << i << ": ";
            for (size_t j = 0; j < bins[i]; ++j) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
        return;
    }
};

}  // namespace yutils