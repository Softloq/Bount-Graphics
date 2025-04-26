/**
 * @file StandardMacros.hpp
 * @brief Standard Window Library Macros. This is included in all window-based headers.
 * @author Brandon Foster (Paradox Gene)
 */

 #ifndef BOUNT_WINDOW_STANDARD_MACROS_HPP
 #define BOUNT_WINDOW_STANDARD_MACROS_HPP
 
 #include <Bount/Core/StandardMacros.hpp>
 
 /**
  * Main Macros:
  * BOUNT_WINDOW_API - Must be prefixed in all window-based classes and functions.
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
     #define BOUNT_WINDOW_EXPORT __declspec(dllexport)
     #define BOUNT_WINDOW_IMPORT __declspec(dllimport)
 #elif defined(BOUNT_CLANG)
     #define BOUNT_WINDOW_EXPORT __attribute__((visibility("default")))
     #define BOUNT_WINDOW_IMPORT
 #elif defined(BOUNT_GCC)
     #define BOUNT_WINDOW_EXPORT __attribute__((visibility("default")))
     #define BOUNT_WINDOW_IMPORT
 #endif
 
 #if defined(BOUNT_WINDOW_BUILD_API)
     #define BOUNT_WINDOW_API BOUNT_WINDOW_EXPORT
 #elif defined(BOUNT_WINDOW_USE_API)
     #define BOUNT_WINDOW_API BOUNT_WINDOW_IMPORT
 #else
     #define BOUNT_WINDOW_API
 #endif
 
 #ifndef BOUNT_WINDOW_EXPORT
     #define BOUNT_WINDOW_EXPORT
 #endif
 
 #ifndef BOUNT_WINDOW_IMPORT
     #define BOUNT_WINDOW_IMPORT
 #endif
 
 #ifndef BOUNT_WINDOW_API
     #define BOUNT_WINDOW_API
 #endif
 
 #endif