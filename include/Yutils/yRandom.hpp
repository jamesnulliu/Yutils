#pragma once
#include "Yutils/yConcepts.hpp"
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

namespace yutils
{

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
class yRandUniform
{
public:
    explicit yRandUniform() = default;
    yRandUniform& operator()(const xRandUniform&) = delete;

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
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
std::random_device yRandUniform<_ValTy>::_rd{};

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
thread_local std::default_random_engine yRandUniform<_ValTy>::m_engine{_rd()};

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
std::uniform_real_distribution<double>* yRandUniform<_ValTy>::m_distribution{nullptr};

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
class yRandNormal
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
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
std::random_device yRandNormal<_ValTy>::_rd{};

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
thread_local std::default_random_engine yRandNormal<_ValTy>::m_engine{_rd()};

template <class _ValTy>
    requires std::integral<_ValTy> || IsAnyOf<std::remove_cv_t<_ValTy>, float, double>
std::normal_distribution<double>* yRandNormal<_ValTy>::m_distribution{nullptr};

}  // namespace yutils