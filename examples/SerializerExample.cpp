#include "Yutils/Logger.hpp"
#include "Yutils/Serializer.hpp"
#include <cstdio>
#include <string>
#include <vector>

using namespace yutils;

// =============================================================================
// Example: Serilize std::vector<double> to std::vector<std::byte>
// -----------------------------------------------------------------------------
void test_bytesSerialization()
{
    YINFO("\n{:=<80}", ":) Bytes serialization for std::vector<double, 5> ");

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // To serialize objects to type `RawT`, you need to use function `serialize`
    // provided by class `yutils::Serializer<RawT>`.
    // In the following example, we serialize `data` (which is a vector of
    // double) to a `RawT`=`std::vector<std::byte>`.
    auto serialized =
        // `serialize` is a static method of class `yutils::Serializer<RawT>`.
        // It takes an object of type `ObjT` and returns a `RawT`.
        yutils::Serializer<std::vector<std::byte>>::serialize(data);
    std::string bytesStr;
    for (const auto& byte : serialized) {
        bytesStr += std::format("{:02X} ", static_cast<int>(byte));
    }
    YTRACE("Serialized: {}", bytesStr);
    // To deserialize objects from type `RawT`, you need to use function
    // `deserialize` provided by class `yutils::Serializer<RawT>`.
    // In the following example, we deserialize `serialized` (which is a
    // `RawT`=`std::vector<std::byte>`) to a `ObjT`=`std::vector<double>`.
    auto deserialized =
        yutils::Serializer<std::vector<std::byte>>::deserialize<decltype(data)>(
            serialized);
    std::string doubleStr;
    for (const auto& val : deserialized) {
        doubleStr += std::format("{:.1f} ", val);
    }
    YTRACE("Deserialized: {}", doubleStr);
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
    YINFO("\n{:=<80}", ":) String serialization for struct User ");
    User user = {"Tom", 18};
    auto serialized = Serializer<std::string>::serialize(user);
    YTRACE("Serialized: {}", serialized);
    User deserialized = Serializer<std::string>::deserialize<User>(serialized);
    YTRACE("Deserialized: name={}, age={}", deserialized.name,
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
    // Define some types for convenience.
    using RawT = std::vector<int>;
    using MyT = Serializer<RawT>;
    using BaseT = BaseSerializer<MyT>;

    // Using `serialize` and `deserialize` from BaseSerializer is required
    // because `Serializer` is a template class.
    using BaseT::deserialize;
    using BaseT::serialize;

public:
    // Mark the template functions as deleted;
    // We will only use the specialization for this template.
    template <typename ObjT>
    static RawT serializeImpl(const ObjT& object) = delete;
    template <typename ObjT>
    static ObjT deserializeImpl(const RawT& rawData) = delete;

    // Specialize the template functions for struct User.
    // Declaration for `serializeImpl`.
    template <>
    RawT serializeImpl(const User& object);
    // Declaration for `deserializeImpl`.
    template <>
    User deserializeImpl(const RawT& rawData);
};

// Define the specialization for the template function `serializeImpl`.
template <>
std::vector<int> Serializer<std::vector<int>>::serializeImpl(const User& object)
{
    RawT rawData(sizeof(char) * object.name.size() + sizeof(int));
    std::memcpy(rawData.data(), object.name.data(), object.name.size());
    std::memcpy(rawData.data() + object.name.size(), &object.age, sizeof(int));
    return rawData;
}

// Define the specialization for the template function `deserializeImpl`.
template <>
User Serializer<std::vector<int>>::deserializeImpl(const RawT& object)
{
    User user;
    user.name = std::string(object.begin(), object.begin() + sizeof(char) * 3);
    user.age = *reinterpret_cast<const int*>(object.data() + sizeof(char) * 3);
    return user;
}
}  // namespace yutils

void test_serializeUser2VectorInt()
{
    YINFO("\n{:=<80}", ":) std::vector<int> serialization for struct User ");
    User user = {"Tom", 18};
    auto serialized = Serializer<std::vector<int>>::serialize(user);
    std::string intStr;
    for (const auto& byte : serialized) {
        intStr += std::format("{:08} ", byte);
    }
    YTRACE("Serialized: {}", intStr);
    User deserialized =
        Serializer<std::vector<int>>::deserialize<User>(serialized);
    YTRACE("Deserialized: name={}, age={}", deserialized.name,
           deserialized.age);
    std::puts("");
}
// =============================================================================

int main()
{
    test_bytesSerialization();
    test_serializeUser2String();
    test_serializeUser2VectorInt();
    return 0;
}
