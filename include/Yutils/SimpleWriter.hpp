#pragma once
#include <format>
#include <fstream>
#include <initializer_list>
#include <string>
#include <vector>

#include "Yutils/PreDefined.hpp"

namespace yutils
{
class SimpleWriter
{
public:
    YUTILS_API explicit SimpleWriter(const std::string& filename, size_t numColumns, bool autoFlush = false);
    YUTILS_API SimpleWriter(const SimpleWriter&) = delete;
    YUTILS_API SimpleWriter& operator=(const SimpleWriter&) = delete;
    YUTILS_API ~SimpleWriter();

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

    YUTILS_API void flush();

private:
    std::ofstream m_file;
    size_t m_numColumns;
    bool m_autoFlush;
    std::vector<std::vector<std::string>> m_buffer;
};
}  // namespace yutils
