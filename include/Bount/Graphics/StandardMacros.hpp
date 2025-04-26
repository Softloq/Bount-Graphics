/**
 * @file StandardMacros.hpp
 * @brief Standard Graphics Library Macros. This is included in all graphics library headers.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_GRAPHICS_STANDARD_MACROS_HPP
#define BOUNT_GRAPHICS_STANDARD_MACROS_HPP

#include <Bount/Core/StandardMacros.hpp>

/**
 * Main Macros:
 * BOUNT_GRAPHICS_API - Must be prefixed in all graphics library classes and functions.
 *
 * BOUNT_DEBUG - Defined when debug information should be provided.
 * 
 * BOUNT_MSVC  - Defined when the libraries are compiled with Microsoft C++ compiler.
 * BOUNT_CLANG - Defined when the libraries are compiled with Clang C++ compiler.
 * BOUNT_GCC   - Defined when the libraries are compiled with GNU C++ compiler.
 * 
 * BOUNT_WINDOWS - Defined when the libraries are compiled for Windows.
 * BOUNT_LINUX   - Defined when the libraries are compiled for Linux.
 * BOUNT_MACOS   - Defined when the libraries are compiled for macOS.
 */

#if defined(BOUNT_MSVC)
    #define BOUNT_GRAPHICS_EXPORT __declspec(dllexport)
    #define BOUNT_GRAPHICS_IMPORT __declspec(dllimport)
#elif defined(BOUNT_CLANG)
    #define BOUNT_GRAPHICS_EXPORT __attribute__((visibility("default")))
    #define BOUNT_GRAPHICS_IMPORT
#elif defined(BOUNT_GCC)
    #define BOUNT_GRAPHICS_EXPORT __attribute__((visibility("default")))
    #define BOUNT_GRAPHICS_IMPORT
#endif

#if defined(BOUNT_GRAPHICS_BUILD_API)
    #define BOUNT_GRAPHICS_API BOUNT_GRAPHICS_EXPORT
#elif defined(BOUNT_GRAPHICS_USE_API)
    #define BOUNT_GRAPHICS_API BOUNT_GRAPHICS_IMPORT
#else
    #define BOUNT_GRAPHICS_API
#endif

#ifndef BOUNT_GRAPHICS_EXPORT
    #define BOUNT_GRAPHICS_EXPORT
#endif

#ifndef BOUNT_GRAPHICS_IMPORT
    #define BOUNT_GRAPHICS_IMPORT
#endif

#ifndef BOUNT_GRAPHICS_API
    #define BOUNT_GRAPHICS_API
#endif

#endif