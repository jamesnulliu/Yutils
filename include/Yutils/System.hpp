#pragma once

#include <cstdlib>

#ifndef YUTILS_CXX_VERSION
    #if defined(_MSC_VER)  // MSVC
        #if _HAS_CXX23     // C++23
            #define YUTILS_CXX_VERSION 23
        #else  // Other versions
static_assert(false, "C++23 is required");
        #endif
    #else                           // GCC or Clang
        #if __cplusplus >= 202300L  // C++23
            #define YUTILS_CXX_VERSION 23
        #else  // Other versions
static_assert(false, "C++23 is required");
        #endif
    #endif
#endif

#if defined(_WIN32) || defined(__WIN32__)
    #if defined(YUTILS_EXPORT)
        #define YUTILS_API __declspec(dllexport)
    #elif defined(YUTILS_IMPORT)
        #define YUTILS_API __declspec(dllimport)
    #else
        #define YUTILS_API
    #endif
#else
    #if defined(YUTILS_EXPORT)
        #define YUTILS_API __attribute__((visibility("default")))
    #else
        #define YUTILS_API
    #endif
#endif
