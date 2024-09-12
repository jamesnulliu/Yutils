#pragma once

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <format>
#include <spdlog/spdlog.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "Yutils/Common.hpp"
#include "Yutils/TypeTraits.hpp"

namespace yutils
{

template <typename DerivedT>
class BaseSerializer
{
public:
    using RawT = yutils::type_traits::GetInnerType_t<DerivedT>;

    /**
     * @brief Serialize an object to a raw data.
     *
     * @tparam ObjT Type of the object to be serialized.
     * @param object Object to be serialized.
     * @return RawT Raw data.
     */
    template <typename ObjT>
    static RawT serialize(const ObjT& object)
    {
        return DerivedT::template serializeImpl<ObjT>(object);
    }

    /**
     * @brief Deserialize raw data to an object.
     *
     * @tparam ObjT Type of the object to be deserialized.
     * @param rawData Raw data.
     * @return ObjT Deserialized object.
     */
    template <typename ObjT>
    static ObjT deserialize(const RawT& rawData)
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
    template <typename ObjT>
    static std::vector<std::byte> serializeImpl(const ObjT& object)
    {
        // IF: std::vector<std::byte>
        if constexpr (std::is_same_v<ObjT, std::vector<std::byte>>) {
            return object;
        }
        // ELIF: Scalar type or std containers with stack-allocated memory
        else if constexpr (std::is_trivially_copyable_v<ObjT>) {
            std::vector<std::byte> data(sizeof(ObjT));
            std::memcpy(data.data(), &object, sizeof(ObjT));
            return data;
        }
        // ELIF: Std containers with heap-allocated memory
        else if constexpr (yutils::IsRange<ObjT>::value) {
            std::vector<std::byte> data(sizeof(typename ObjT::value_type) *
                                        object.size());
            std::memcpy(data.data(), object.data(), data.size());
            return data;
        }
        // ELSE: Unsupported type
        else {
            static_assert(false, "Unsupported type for serialization.");
        }
    }

    template <typename ObjT>
    static ObjT deserializeImpl(const std::vector<std::byte>& rawData)
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
    template <typename ObjT>
    static std::string serializeImpl(const ObjT& object)
    {
        if constexpr (std::is_same_v<ObjT, std::string>) {
            return object;
        } else if constexpr (std::is_arithmetic_v<ObjT>) {
            return std::to_string(object);
        } else if constexpr (std::is_enum_v<ObjT>) {
            return std::to_string(
                static_cast<std::underlying_type_t<ObjT>>(object));
        } else {
            // [todo]
            //   - Better support for arithmetic types.
            //   - Add support for std::vector<T> and std::array<T, N>.
            //   - Add support for std::pair<T1, T2> and std::tuple<Ts...>.
            //   - Add support for std::map<K, V> and std::unordered_map<K, V>.
            //   - Add support for std::set<T> and std::unordered_set<T>.
            std::stringstream ss;
            ss << object;
            return ss.str();
        }
    }

    template <typename ObjT>
    static ObjT deserializeImpl(const std::string& rawData)
    {
        if constexpr (std::is_same_v<ObjT, std::string>) {
            return rawData;
        } else if constexpr (std::is_same_v<ObjT, bool>) {
            auto falseFlag = {"false", "0", "False", "FALSE"};
            return std::find(falseFlag.begin(), falseFlag.end(), rawData) ==
                   falseFlag.end();
        } else if constexpr (std::is_enum_v<ObjT>) {
            return static_cast<ObjT>(std::stoi(rawData));
        } else {
            // [todo]
            //   - Better support for arithmetic types.
            //   - Add support for std::vector<T> and std::array<T, N>.
            //   - Add support for std::pair<T1, T2> and std::tuple<Ts...>.
            //   - Add support for std::map<K, V> and std::unordered_map<K, V>.
            //   - Add support for std::set<T> and std::unordered_set<T>.
            ObjT result;
            std::stringstream ss(rawData);
            ss >> result;
            if (ss.fail()) {
                throw std::runtime_error(spdlog::fmt_lib::format(
                    "Failed when converting rawData to original Type: {}.",
                    yutils::type_traits::typeName<ObjT>()));
            }
            return result;
        }
    }
};
}  // namespace yutils