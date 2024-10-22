#include "Yutils/SimpleCSV.hpp"
#include <filesystem>

namespace yutils
{
SimpleCSV::SimpleCSV(size_t numColumns) : m_numColumns(numColumns)
{
}

SimpleCSV::~SimpleCSV()
{
}

void SimpleCSV::resizeCol(size_t numColumns)
{
    m_numColumns = numColumns;
    for (auto& row : m_buffer) { row.resize(numColumns); }
}

void SimpleCSV::insertRow(std::size_t rowIdx,
                          const std::vector<std::string>& row)
{
    if (row.size() != m_numColumns) {
        throw std::runtime_error("Number of columns does not match");
    }
    m_buffer.insert(m_buffer.begin() + rowIdx, row);
}

void SimpleCSV::appendRow(const std::vector<std::string>& row)
{
    if (row.size() != m_numColumns) {
        throw std::runtime_error("Number of columns does not match");
    }
    m_buffer.emplace_back(row);
}

void SimpleCSV::dump(std::ostream& out, bool clearBuffer) const
{
    for (const auto& row : m_buffer) {
        for (size_t i = 0; i < m_numColumns; ++i) {
            out << row[i];
            if (i < m_numColumns - 1) {
                out << ",";
            }
        }
        out << "\n";
    }

    if (clearBuffer) {
        const_cast<SimpleCSV*>(this)->m_buffer.clear();
    }
}
}  // namespace yutils
