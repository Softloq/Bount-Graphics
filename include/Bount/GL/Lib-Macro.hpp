#ifndef BOUNT_GL_LIB_MACRO_HPP
#define BOUNT_GL_LIB_MACRO_HPP

#if defined(_DLL)
    #define BOUNT_GL_EXPORT __declspec(dllexport)
    #define BOUNT_GL_IMPORT __declspec(dllimport)
#elif defined(__PIC__) || defined(__pic__)
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