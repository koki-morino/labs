#ifndef MY_DEFS_H
#define MY_DEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

// NOTE: Any macro that starts with underscore is reserved.
// Don't use such a name. e.g. _MY_INTERNAL_MACRO

typedef enum
{
    MY_SUCCESS,
    MY_ERROR
} MY_result;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define MY_PLATFORM_WINDOWS
#endif

#if defined(__linux__) || defined(__gnu_linux__)
#define MY_PLATFORM_LINUX
#endif

#if !defined(MY_PLATFORM_WINDOWS) && !defined(MY_PLATFORM_LINUX)
#error "Unsupported platform"
#endif

// MinGW uses __declspec() to export symbol like MSVC.
#if defined(MY_PLATFORM_WINDOWS)
// TODO: Search for when to use __declspec(dllimport).
#define MY_API __declspec(dllexport)
#else
#define MY_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif
