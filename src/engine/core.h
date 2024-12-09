#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

namespace stellar {
namespace core {

// 定义一些核心类型和常量
using uint = unsigned int;
using byte = unsigned char;

// 定义平台相关的宏
#if defined(_WIN32)
    #define STELLAR_PLATFORM_WINDOWS
#elif defined(__linux__)
    #define STELLAR_PLATFORM_LINUX
#elif defined(__APPLE__)
    #define STELLAR_PLATFORM_MACOS
#endif

// API导出宏
#ifdef STELLAR_PLATFORM_WINDOWS
    #ifdef STELLAR_BUILD_DLL
        #define STELLAR_API __declspec(dllexport)
    #else
        #define STELLAR_API __declspec(dllimport)
    #endif
#else
    #define STELLAR_API
#endif

} // namespace core
} // namespace stellar

#endif // ENGINE_CORE_H 