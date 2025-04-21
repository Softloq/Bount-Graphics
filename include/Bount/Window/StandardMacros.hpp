/**
 * @file StandardMacros.hpp
 * @brief Standard Window Library Macros. This is included in all window library headers.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_WINDOW_STANDARD_MACROS_HPP
#define BOUNT_WINDOW_STANDARD_MACROS_HPP

#include <Bount/GL/StandardMacros.hpp>

 /**
  * Main Macros:
  * BOUNT_WINDOW_API - Must be prefixed in all window classes and functions.
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

#define BOUNT_WINDOW_API BOUNT_GL_API

#endif