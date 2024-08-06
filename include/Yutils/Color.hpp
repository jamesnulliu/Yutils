#pragma once

#define YUTILS_COLOR_FG_BLACK "30"
#define YUTILS_COLOR_FG_RED "31"
#define YUTILS_COLOR_FG_GREEN "32"
#define YUTILS_COLOR_FG_YELLOW "33"
#define YUTILS_COLOR_FG_BLUE "34"
#define YUTILS_COLOR_FG_MAGENTA "35"
#define YUTILS_COLOR_FG_CYAN "36"
#define YUTILS_COLOR_FG_WHITE "37"

#define YUTILS_COLOR_BG_BLACK "40"
#define YUTILS_COLOR_BG_RED "41"
#define YUTILS_COLOR_BG_GREEN "42"
#define YUTILS_COLOR_BG_YELLOW "43"
#define YUTILS_COLOR_BG_BLUE "44"
#define YUTILS_COLOR_BG_MAGENTA "45"
#define YUTILS_COLOR_BG_CYAN "46"
#define YUTILS_COLOR_BG_WHITE "47"

#define YUTILS_COLOR_BOLD "1"
#define YUTILS_COLOR_DIM "2"
#define YUTILS_COLOR_ITALIC "3"
#define YUTILS_COLOR_UNDERLINE "4"
#define YUTILS_COLOR_BLINK "5"
#define YUTILS_COLOR_INVERSE "7"
#define YUTILS_COLOR_HIDE "8"

#define YUTILS_COLOR_FUNC_RESET "\033[0m"

#define YUTILS_COLOR_FUNC_GEN_1(attr1) "\033[" attr1 "m"
#define YUTILS_COLOR_FUNC_GEN_2(attr1, attr2)                                       \
    "\033[" attr1 ";" attr2 "m"
#define YUTILS_COLOR_FUNC_GEN_3(attr1, attr2, attr3)                                \
    "\033[" attr1 ";" attr2 ";" attr3 "m"
