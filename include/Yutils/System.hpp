#pragma once

#include <cstdlib>

#ifndef YUTILS_CXX_VERSION
    #if defined(_MSC_VER)  // MSVC
        #if _HAS_CXX23     // C++23
            #define YUTILS_CXX_VERSION 23
        #elif _HAS_CXX20  // C++20
            #define YUTILS_CXX_VERSION 20
        #elif _HAS_CXX17  // C++17
            #define YUTILS_CXX_VERSION 17
        #else
static_assert(false, "Unsupported C++ version");
        #endif
    #else                           // GCC or Clang
        #if __cplusplus >= 202300L  // C++23
            #define YUTILS_CXX_VERSION 23
        #elif __cplusplus >= 202002L  // C++20
            #define YUTILS_CXX_VERSION 20
        #elif __cplusplus >= 201703L  // C++17
            #define YUTILS_CXX_VERSION 17
        #else
static_assert(false, "Unsupported C++ version");
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
