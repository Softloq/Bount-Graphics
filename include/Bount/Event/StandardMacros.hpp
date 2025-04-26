/**
 * @file StandardMacros.hpp
 * @brief Standard Event Library Macros. This is included in all event headers.
 * @author Brandon Foster (Paradox Gene)
 */

 #ifndef BOUNT_EVENT_STANDARD_MACROS_HPP
 #define BOUNT_EVENT_STANDARD_MACROS_HPP
 
 #include <Bount/Core/StandardMacros.hpp>
 
 /**
  * Main Macros:
  * BOUNT_EVENT_API - Must be prefixed in all event-based classes and functions.
  *
  * BOUNT_DEBUG - Defined when debug information should be provided.
  * 
  * BOUNT_MSVC  - Defined when the libraries are compiled with Microsoft C++ compiler.
  * BOUNT_CLANG - Defined when the libraries are compiled with Clang C++ compiler.
  * BOUNT_GCC   - Defined when the libraries are compiled with GNU C++ compiler.
  * 
  * BOUNT_EVENTS - Defined when the libraries are compiled for Windows.
  * BOUNT_LINUX   - Defined when the libraries are compiled for Linux.
  * BOUNT_MACOS   - Defined when the libraries are compiled for macOS.
  */
 
 #if defined(BOUNT_MSVC)
     #define BOUNT_EVENT_EXPORT __declspec(dllexport)
     #define BOUNT_EVENT_IMPORT __declspec(dllimport)
 #elif defined(BOUNT_CLANG)
     #define BOUNT_EVENT_EXPORT __attribute__((visibility("default")))
     #define BOUNT_EVENT_IMPORT
 #elif defined(BOUNT_GCC)
     #define BOUNT_EVENT_EXPORT __attribute__((visibility("default")))
     #define BOUNT_EVENT_IMPORT
 #endif
 
 #if defined(BOUNT_EVENT_BUILD_API)
     #define BOUNT_EVENT_API BOUNT_EVENT_EXPORT
 #elif defined(BOUNT_EVENT_USE_API)
     #define BOUNT_EVENT_API BOUNT_EVENT_IMPORT
 #else
     #define BOUNT_EVENT_API
 #endif
 
 #ifndef BOUNT_EVENT_EXPORT
     #define BOUNT_EVENT_EXPORT
 #endif
 
 #ifndef BOUNT_EVENT_IMPORT
     #define BOUNT_EVENT_IMPORT
 #endif
 
 #ifndef BOUNT_EVENT_API
     #define BOUNT_EVENT_API
 #endif
 
 #endif