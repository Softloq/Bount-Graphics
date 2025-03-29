#ifndef BOUNT_GL_SYSTEM_HPP
#define BOUNT_GL_SYSTEM_HPP

#include "Bount/GL/Lib-Macro.hpp"
#include <mutex>

namespace Bount::GL
{
class System
{
    static System* _instance;
    static std::once_flag _init;

public:
    BOUNT_GL_API System(const System&) = delete;
    BOUNT_GL_API System& operator=(const System&) = delete;
    
    BOUNT_GL_API static System& instance();
    
    BOUNT_GL_API bool initialize();
    BOUNT_GL_API void shutdown();

private:
    BOUNT_GL_API System();
    BOUNT_GL_API ~System();
};
}

#endif
