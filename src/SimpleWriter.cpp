#include "Yutils/SimpleWriter.hpp"

namespace yutils
{
SimpleWriter::SimpleWriter(const std::string& filename, size_t numColumns, bool autoFlush)
    : m_numColumns(numColumns), m_autoFlush(autoFlush)
{
    m_file.open(filename);
    if (!m_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

SimpleWriter::~SimpleWriter()
{
    if (!m_buffer.empty()) {
        flush();
    }
    m_file.close();
}

void SimpleWriter::flush()
{
    for (const auto& row : m_buffer) {
        for (size_t i = 0; i < m_numColumns; ++i) {
            m_file << row[i];
            if (i < m_numColumns - 1) {
                m_file << ",";
            }
        }
        m_file << "\n";
    }
    m_buffer.clear();
    m_file.flush();
}
}  // namespace yutils
