/**
 * @file StandardMacros.hpp
 * @brief Standard Graphics Library Macros. This is included in all graphics library headers.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_GL_STANDARD_MACROS_HPP
#define BOUNT_GL_STANDARD_MACROS_HPP

#include <Bount/Core/StandardMacros.hpp>

/**
 * Main Macros:
 * BOUNT_GL_API - Must be prefixed in all graphics library classes and functions.
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
    #define BOUNT_GL_EXPORT __declspec(dllexport)
    #define BOUNT_GL_IMPORT __declspec(dllimport)
#elif defined(BOUNT_CLANG)
    #define BOUNT_GL_EXPORT __attribute__((visibility("default")))
    #define BOUNT_GL_IMPORT
#elif defined(BOUNT_GCC)
    #define BOUNT_GL_EXPORT __attribute__((visibility("default")))
    #define BOUNT_GL_IMPORT
#endif

#if defined(BOUNT_GL_BUILD_API)
    #define BOUNT_GL_API BOUNT_GL_EXPORT
#elif defined(BOUNT_GL_USE_API)
    #define BOUNT_GL_API BOUNT_GL_IMPORT
#else
    #define BOUNT_GL_API
#endif

#ifndef BOUNT_GL_EXPORT
    #define BOUNT_GL_EXPORT
#endif

#ifndef BOUNT_GL_IMPORT
    #define BOUNT_GL_IMPORT
#endif

#ifndef BOUNT_GL_API
    #define BOUNT_GL_API
#endif

#endif