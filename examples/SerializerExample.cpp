#include <cstdio>
#include <format>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

#include <Yutils/Common.hpp>
#include <Yutils/Serializer.hpp>
#include <Yutils/TypeTraits.hpp>

using namespace yutils;

using spdlog::fmt_lib::format;

// =============================================================================
// Example: Serilize std::vector<double> to std::vector<std::byte>
// -----------------------------------------------------------------------------
void test_bytesSerialization()
{
    spdlog::info("\n{:=<80}",
                 ":) Bytes serialization for std::vector<double, 5> ");

    // Serializer<RawT> is a template class that provides functions to serialize
    // and deserialize objects of type `ObjT` to/from type `RawT`.
    using BytesSerializer = Serializer<std::vector<std::byte>>;

    spdlog::info("Serializer Type: {}",
                 yutils::type_traits::typeName<BytesSerializer>());

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // To serialize objects to type `RawT`, you need to use function `serialize`
    // provided by class `yutils::Serializer<RawT>`.
    // In the following example, we serialize `data` (which is a vector of
    // double) to a `RawT`=`std::vector<std::byte>`.
    auto serialized =
        // `serialize` is a static method of class `yutils::Serializer<RawT>`.
        // It takes an object of type `ObjT` and returns a `RawT`.
        BytesSerializer::serialize(data);
    std::string bytesStr;
    for (const auto& byte : serialized) {
        bytesStr += format("{:02X} ", static_cast<int>(byte));
    }
    spdlog::trace("Serialized: {}", bytesStr);
    auto deserialized =
        // To deserialize objects from type `RawT`, you need to use function
        // `deserialize` provided by class `yutils::Serializer<RawT>`.
        // In the following example, we deserialize `serialized` (which is a
        // `RawT`=`std::vector<std::byte>`) to a `ObjT`=`std::vector<double>`.
        BytesSerializer::deserialize<decltype(data)>(serialized);
    std::string doubleStr;
    for (const auto& val : deserialized) {
        doubleStr += format("{:.1f} ", val);
    }
    spdlog::trace("Deserialized: {}", doubleStr);
    std::puts("");
}
// =============================================================================

// =============================================================================
// Example: Serialize struct User to string
// -----------------------------------------------------------------------------
struct User
{
    std::string name;
    int age;
};

template <>
std::string yutils::Serializer<std::string>::serializeImpl(const User& object)
{
    return object.name + ";" + std::to_string(object.age);
}

template <>
User Serializer<std::string>::deserializeImpl(const std::string& rawData)
{
    User user;
    auto pos = rawData.find(';');
    user.name = rawData.substr(0, pos);
    user.age = std::stoi(rawData.substr(pos + 1));
    return user;
}

void test_serializeUser2String()
{
    using StrSerializer = Serializer<std::string>;

    spdlog::info("Serializer Type: {}",
                 yutils::type_traits::typeName<StrSerializer>());

    spdlog::info("\n{:=<80}", ":) String serialization for struct User ");
    User user = {"Tom", 18};
    auto serialized = StrSerializer::serialize(user);
    spdlog::trace("Serialized: {}", serialized);
    User deserialized = StrSerializer::deserialize<User>(serialized);
    spdlog::trace("Deserialized: name={}, age={}", deserialized.name,
                  deserialized.age);
    std::puts("");
}
// -----------------------------------------------------------------------------

// =============================================================================
// Example: Defined a new Serializer to serialize object to std::vector<int>
// -----------------------------------------------------------------------------
namespace yutils
{
// Define a new Serializer for std::vector<int>.
// You should put the definition of the new Serializer in a header file.
// You can implement the specialized template functions (`serializeImpl` and
// `deserializeImpl`) in a source file.
template <>
class Serializer<std::vector<int>>
    // CRTP: Inherit Your Serilizer from BaseSerializer.
    : public BaseSerializer<Serializer<std::vector<int>>>
{
public:
    // Mark the template functions as deleted;
    // We will only use some specializations for this template.
    template <typename ObjT>
    static std::vector<int> serializeImpl(const ObjT& object) = delete;
    template <typename ObjT>
    static ObjT deserializeImpl(const std::vector<int>& rawData) = delete;
};

// Define the specialization for the template function `serializeImpl`.
template <>
std::vector<int> Serializer<std::vector<int>>::serializeImpl(const User& object)
{
    std::vector<int> rawData(sizeof(char) * object.name.size() + sizeof(int));
    std::memcpy(rawData.data(), object.name.data(), object.name.size());
    std::memcpy(rawData.data() + object.name.size(), &object.age, sizeof(int));
    return rawData;
}

// Define the specialization for the template function `deserializeImpl`.
template <>
User Serializer<std::vector<int>>::deserializeImpl(const std::vector<int>& object)
{
    User user;
    user.name = std::string(object.begin(), object.begin() + sizeof(char) * 3);
    user.age = *reinterpret_cast<const int*>(object.data() + sizeof(char) * 3);
    return user;
}
}  // namespace yutils

void test_serializeUser2VectorInt()
{
    using VecIntSerializer = Serializer<std::vector<int>>;

    spdlog::info("Serializer Type: {}",
                 yutils::type_traits::typeName<VecIntSerializer>());

    spdlog::info("\n{:=<80}",
                 ":) std::vector<int> serialization for struct User ");
    User user = {"Tom", 18};
    auto serialized = VecIntSerializer::serialize(user);
    std::string intStr;
    for (const auto& byte : serialized) {
        intStr += format("{:08} ", byte);
    }
    spdlog::trace("Serialized: {}", intStr);
    User deserialized = VecIntSerializer::deserialize<User>(serialized);
    spdlog::trace("Deserialized: name={}, age={}", deserialized.name,
                  deserialized.age);
    std::puts("");
}
// =============================================================================

int main()
{
    spdlog::set_level(spdlog::level::trace);
    test_bytesSerialization();
    test_serializeUser2String();
    test_serializeUser2VectorInt();
    return 0;
}
