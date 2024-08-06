#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Yutils/Serializer.hpp"
#include "Yutils/System.hpp"

namespace yutils
{
class SimpleCSV
{
public:
    YUTILS_API explicit SimpleCSV(std::size_t numColumns);
    SimpleCSV(const SimpleCSV&) = delete;
    SimpleCSV& operator=(const SimpleCSV&) = delete;
    YUTILS_API ~SimpleCSV();

public:

public:
    std::size_t numRows() const
    {
        return m_buffer.size();
    }

    std::size_t numCols() const
    {
        return m_numColumns;
    }

    /// @NotImplemented
    YUTILS_API const std::vector<std::string>& getRow(std::size_t rowIdx) const;
    /// @NotImplemented
    YUTILS_API std::vector<std::string>& getRow(std::size_t rowIdx);

    /// @NotImplemented
    YUTILS_API const std::vector<std::string&> getCol(std::size_t colIdx) const;
    /// @NotImplemented
    YUTILS_API std::vector<std::string&> getCol(std::size_t colIdx);

    /// @NotImplemented
    YUTILS_API const std::string& getCell(std::size_t rowIdx,
                                          std::size_t colIdx) const;
    /// @NotImplemented
    YUTILS_API std::string& getCell(std::size_t rowIdx, std::size_t colIdx);

    /// @NotImplemented
    YUTILS_API void setCell(std::size_t rowIdx, std::size_t colIdx,
                            const std::string& value);

    /// @NotImplemented
    YUTILS_API const std::vector<std::string>& operator[](
        std::size_t rowIdx) const;
    /// @NotImplemented
    YUTILS_API std::vector<std::string>& operator[](std::size_t rowIdx);

    YUTILS_API void insertRow(std::size_t rowIdx,
                              const std::vector<std::string>& row);

    YUTILS_API void appendRow(const std::vector<std::string>& row);

    template <typename... ElemTs>
    static std::vector<std::string> makeStrVec(ElemTs&&... elems)
    {
        return {Serializer<std::string>::serialize(elems)...};
    }

    YUTILS_API void resizeCol(size_t numColumns);

    YUTILS_API void dump(std::ostream& out, bool clearBuffer = false) const;

private:
    std::size_t m_numColumns;
    std::vector<std::vector<std::string>> m_buffer;
};

}  // namespace yutils
