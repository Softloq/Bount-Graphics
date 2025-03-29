#ifndef BOUNT_GL_WINDOW_HPP
#define BOUNT_GL_WINDOW_HPP

#include "Bount/GL/Lib-Macro.hpp"
#include "Bount/GL/Layer.hpp"

#include <SDL3/SDL.h>

#include <functional>
#include <mutex>

namespace Bount::GL
{
class Window
{
    static Window* _instance;
    static std::once_flag _init;

    LayerGroup _layers;

    SDL_Window* _handle;
    SDL_GLContext _glContext;

public:
    BOUNT_GL_API Window(const Window&) = delete;
    BOUNT_GL_API Window& operator=(const Window&) = delete;
    
    BOUNT_GL_API static Window& instance();
    
    BOUNT_GL_API bool initialize();
    BOUNT_GL_API void shutdown();

    BOUNT_GL_API void run();

    BOUNT_GL_API void show();
    BOUNT_GL_API void hide();

    BOUNT_GL_API void swap();

    BOUNT_GL_API LayerGroup& getLayers();

    BOUNT_GL_API SDL_Window* const getSDLHandle() const;
    BOUNT_GL_API SDL_GLContext const getGLContext() const;

private:
    BOUNT_GL_API Window();
    BOUNT_GL_API ~Window();
};
}

#endif