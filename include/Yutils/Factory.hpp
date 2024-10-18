#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <stdexcept>
#include <typeinfo>
#include <unordered_map>
#include <variant>

#include "Yutils/System.hpp"

namespace yutils
{
template <bool threadSafe, typename KeyT, typename ValT,
          typename MapT = std::unordered_map<KeyT, ValT>>
class Registry
{
public:
    explicit Registry() = default;
    Registry& operator=(const Registry&) = delete;

public:
    void add(const KeyT& key, const ValT& val)
    {
        if constexpr (threadSafe) {
            std::unique_lock<std::shared_mutex> lock(m_mutex);
        }
        m_mapper.emplace(key, val);
    }

    void remove(const KeyT& key)
    {
        if constexpr (threadSafe) {
            std::unique_lock<std::shared_mutex> lock(m_mutex);
        }
        m_mapper.erase(key);
    }

    ValT get(const KeyT& key) const
    {
        if constexpr (threadSafe) {
            std::shared_lock<std::shared_mutex> lock(m_mutex);
        }
        auto it = m_mapper.find(key);
        if (it != m_mapper.end()) {
            return it->second;
        }
        throw std::runtime_error("Key not found.");
    }

private:
    std::conditional_t<threadSafe, std::shared_mutex, std::monostate> m_mutex;
    MapT m_mapper;
};

template <bool threadSafe, typename KeyT,
          typename ValT = std::function<std::shared_ptr<void>()>,
          typename MapT = std::unordered_map<KeyT, ValT>>
class Factory : public Registry<threadSafe, KeyT, ValT, MapT>
{
public:
    using BaseT = Registry<threadSafe, KeyT, ValT, MapT>;

public:
    explicit Factory() = default;
    Factory& operator=(const Factory&) = delete;

public:
    template <typename T>
    void add(const KeyT& key)
    {
        this->BaseT::add(key, []() -> std::shared_ptr<void> {
            return std::make_shared<T>();
        });
    }

    template <typename ObjT = void>
    auto create(const KeyT& key)
    {
        auto creator = this->BaseT::get(key);
        auto ptr = std::static_pointer_cast<ObjT>(creator());
        if (!ptr) {
            throw std::bad_cast();
        }
        return ptr;
    }
};

}  // namespace yutils