#pragma once

#include <cassert>
#include <cstddef>
#include <string_view>

#include "Yutils/Concepts.hpp"
#include "Yutils/System.hpp"

namespace yutils
{

/**
 * @brief Extract the filename from a path.
 *
 * @param path The path of the file.
 * @return std::string_view
 */
constexpr std::string_view extractFilename(std::string_view path)
{
    for (std::size_t i = path.size() - 1; i >= 0; --i) {
        if (path[i] == '/' || path[i] == '\\') {
            return path.substr(i + 1);
        }
    }
    return path;
}

}  // namespace yutils
