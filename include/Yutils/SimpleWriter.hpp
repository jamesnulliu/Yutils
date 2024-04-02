#pragma once
#include <format>
#include <fstream>
#include <initializer_list>
#include <string>
#include <vector>

namespace yutils
{
class SimpleWriter
{
public:
    explicit SimpleWriter(const std::string& filename, size_t numColumns, bool autoFlush = false);
    SimpleWriter(const SimpleWriter&) = delete;
    SimpleWriter& operator=(const SimpleWriter&) = delete;
    ~SimpleWriter();

public:
    template <typename... Args>
    void addRow(Args&&... args)
    {
        if (sizeof...(args) != m_numColumns) {
            throw std::runtime_error("Number of columns does not match");
            return;
        }
        std::vector<std::string> row{std::forward<Args>(args)...};
        m_buffer.push_back(row);

        if (m_autoFlush) {
            flush();
        }
    }

    void flush();

private:
    std::ofstream m_file;
    size_t m_numColumns;
    bool m_autoFlush;
    std::vector<std::vector<std::string>> m_buffer;
};
}  // namespace yutils
