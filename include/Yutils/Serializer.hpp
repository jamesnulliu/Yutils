#pragma once

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <format>
#include <ranges>
#include <spdlog/spdlog.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "Yutils/Common.hpp"

namespace yutils
{

template <typename DerivedT>
class BaseSerializer
{
public:
    template <typename ObjT>
    static auto serialize(const ObjT& object)
    {
        return DerivedT::template serializeImpl<ObjT>(object);
    }

    template <typename ObjT>
    static ObjT deserialize(const auto& rawData)
    {
        return DerivedT::template deserializeImpl<ObjT>(rawData);
    }
};

template <typename RawT>
class Serializer;

/**
 * @brief Object <-> std::vector<std::byte>.
 */
template <>
class Serializer<std::vector<std::byte>>
    : public BaseSerializer<Serializer<std::vector<std::byte>>>
{
public:
    using RawT = std::vector<std::byte>;
    using MyT = Serializer<RawT>;
    using BaseT = BaseSerializer<MyT>;
    using BaseT::deserialize;
    using BaseT::serialize;

public:
    template <typename ObjT>
    static RawT serializeImpl(const ObjT& object)
    {
        // IF: std::vector<std::byte>
        if constexpr (std::is_same_v<ObjT, std::vector<std::byte>>) {
            return object;
        }
        // ELIF: Scalar type or std containers with stack-allocated memory
        else if constexpr (std::is_trivially_copyable_v<ObjT>) {
            RawT data(sizeof(ObjT));
            std::memcpy(data.data(), &object, sizeof(ObjT));
            return data;
        }
        // ELIF: Std containers with heap-allocated memory
        else if constexpr (std::ranges::range<ObjT>) {
            RawT data(sizeof(typename ObjT::value_type) * object.size());
            std::memcpy(data.data(), object.data(), data.size());
            return data;
        }
        // ELSE: Unsupported type
        else {
            static_assert(false, "Unsupported type for serialization.");
        }
    }

    template <typename ObjT>
    static ObjT deserializeImpl(const RawT& rawData)
    {
        // IF: std::vector<std::byte>
        if constexpr (std::is_same_v<ObjT, std::vector<std::byte>>) {
            return rawData;
        }
        // ELIF: Scalar type or containers with stack-allocated memory
        else if constexpr (std::is_trivially_copyable_v<ObjT>) {
            if (rawData.size() != sizeof(ObjT)) {
                throw std::runtime_error(spdlog::fmt_lib::format(
                    "Size of data ({}B) does not match the size of "
                    "the object ({}B) to be deserialized.",
                    rawData.size(), sizeof(ObjT)));
            }
            ObjT result;
            std::memcpy(&result, rawData.data(), sizeof(ObjT));
            return result;
        }
        // ELIF: Containers with heap-allocated memory
        else if constexpr (yutils::IsRange<ObjT>::value) {
            if (rawData.size() % sizeof(typename ObjT::value_type) != 0) {
                throw std::runtime_error(spdlog::fmt_lib::format(
                    "Size of data ({}B) is not a multiple of the size "
                    "of the object ({}B) to be deserialized.",
                    rawData.size(), sizeof(typename ObjT::value_type)));
            }
            ObjT result(rawData.size() / sizeof(typename ObjT::value_type));
            std::memcpy(result.data(), rawData.data(), rawData.size());
            return result;
        }
        // ELSE: Unsupported type
        else {
            static_assert(false, "Unsupported type for deserialization.");
        }
    }
};

/**
 * @brief Object <-> std::string.
 */
template <>
class Serializer<std::string> : public BaseSerializer<Serializer<std::string>>
{
public:
    using RawT = std::string;
    using MyT = Serializer<std::string>;
    using BaseT = BaseSerializer<MyT>;
    using BaseT::deserialize;
    using BaseT::serialize;

public:
    template <typename ObjT>
    static RawT serializeImpl(const ObjT& object)
    {
        if constexpr (std::is_same_v<ObjT, std::string>) {
            return object;
        } else if constexpr (std::is_arithmetic_v<ObjT>) {
            return std::to_string(object);
        } else if constexpr (std::is_enum_v<ObjT>) {
            return std::to_string(
                static_cast<std::underlying_type_t<ObjT>>(object));
        } else {
            std::stringstream ss;
            ss << object;
            return ss.str();
        }
    }

    template <typename ObjT>
    static ObjT deserializeImpl(const RawT& rawData)
    {
        if constexpr (std::is_same_v<ObjT, std::string>) {
            return rawData;
        } else if constexpr (std::is_same_v<ObjT, bool>) {
            auto falseFlag = {"false", "0", "False", "FALSE"};
            return std::ranges::find(falseFlag, rawData) == falseFlag.end();
        } else if constexpr (std::is_enum_v<ObjT>) {
            return static_cast<ObjT>(std::stoi(rawData));
        } else {
            ObjT result;
            std::stringstream ss(rawData);
            ss >> result;
            if (ss.fail()) {
                throw std::runtime_error(spdlog::fmt_lib::format(
                    "Failed when converting rawData to original Type: {}.",
                    typeName<ObjT>()));
            }
            return result;
        }
    }
};
}  // namespace yutils