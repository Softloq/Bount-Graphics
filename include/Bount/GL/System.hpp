#ifndef BOUNT_GL_SYSTEM_HPP
#define BOUNT_GL_SYSTEM_HPP

#include "Bount/GL/Lib-Macro.hpp"
#include <SDL3/SDL.h>
#include <mutex>

namespace Bount::GL
{
class System
{
    static System* _instance;
    static std::once_flag _init;

    bool _sdl_init;
    bool _running;

public:
    BOUNT_GL_API System(const System&) = delete;
    BOUNT_GL_API System& operator=(const System&) = delete;
    
    BOUNT_GL_API static System& instance();
    
    BOUNT_GL_API bool initialize();
    BOUNT_GL_API void shutdown();

    BOUNT_GL_API void game_loop();

private:
    BOUNT_GL_API System();
    BOUNT_GL_API ~System();
};
}

#endif
