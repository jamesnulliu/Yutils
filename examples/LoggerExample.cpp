#include <Yutils/Color.hpp>
#include <Yutils/Common.hpp>
#include <fstream>

// YLOG_OSTREAM is std::out by default.
// However, If you want to log to file, you can define YLOG_OSTREAM as a
// std::ofstream before including <Yutils/Logger.hpp>.
//// std::ofstream fout("log.txt");
//// #define YLOG_OSTREAM fout

// You can disable some log levels. The default YLOG_LEVEL is 5, which means all
// log levels are enabled.
// | Log Function |   Enable If    |
// | ------------ | -------------- |
// | YTRACE       | YLOG_LEVEL > 4 |
// | YINFO        | YLOG_LEVEL > 3 |
// | YWARNING     | YLOG_LEVEL > 2 |
// | YERROR       | YLOG_LEVEL > 1 |
// | YCRITICAL    | YLOG_LEVEL > 0 |
#define YLOG_LEVEL 4  // Now YTARCE won't printed.

// There is a default format of log functions. If you are not satisfied with it,
// you can define the format before including <Yutils/Logger.hpp> to overwrite
// it.

#define _HOW_YTRACE                                                            \
    YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_WHITE)                             \
    "(^v^)[{}|{}]: {}" YUTILS_COLOR_FUNC_RESET "\n", "TRACE", __FUNCTION__

#define _HOW_YINFO                                                             \
    YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_GREEN)                             \
    "(O.O)[{}|{}]: {}" YUTILS_COLOR_FUNC_RESET "\n", "TRACE", __FUNCTION__

#define _HOW_YWARNING                                                          \
    YUTILS_COLOR_FUNC_GEN_1(YUTILS_COLOR_FG_YELLOW)                            \
    "(@o@)[{}|{}]: {}" YUTILS_COLOR_FUNC_RESET "\n", "TRACE", __FUNCTION__

#define _HOW_YERROR                                                            \
    YUTILS_COLOR_FUNC_GEN_2(YUTILS_COLOR_FG_RED, YUTILS_COLOR_ITALIC)          \
    "(x_x)[{}|{}]: {}" YUTILS_COLOR_FUNC_RESET "\n", "TRACE", __FUNCTION__

#define _HOW_YCRITICAL                                                         \
    YUTILS_COLOR_FUNC_GEN_3(YUTILS_COLOR_FG_CYAN, YUTILS_COLOR_BG_MAGENTA,     \
                            YUTILS_COLOR_UNDERLINE)                            \
    "($~$)[{}|{}]: {}" YUTILS_COLOR_FUNC_RESET "\n", "TRACE", __FUNCTION__

#include <Yutils/Logger.hpp>

int main()
{
    YTRACE("[{:0>2}] I am {}", 1, "YTRACE");
    YINFO("[{:0>2}] I am {}", 2, "YINFO");
    YWARNING("[{:0>2}] I am {}", 3, "YWARNING");
    YERROR("[{:0>2}] I am {}", 4, "YERROR");
    YCRITICAL("[{:0>2}] I am {}", 5, "YCRITICAL");
}