#pragma once

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