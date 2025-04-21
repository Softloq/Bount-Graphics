#include "Bount/GL/Precompiled.hpp"
#include "Bount/Window/Subsystem.hpp"

namespace Bount::Window
{
BOUNT_WINDOW_API Subsystem_::Subsystem_() noexcept
    : _handle(nullptr)
    , _glContext(nullptr)
{

}
    
BOUNT_WINDOW_API void Subsystem_::onStartup()
{
    // Create SDL window
    _handle = SDL_CreateWindow("Bount Graphics Window", 800, 600, SDL_WINDOW_OPENGL);
    if (!_handle)
    {
        String error_msg = String("Failed to create SDL window: ") + SDL_GetError();
        throw std::exception(error_msg.c_str());
    }
    SDL_HideWindow(_handle);

    // Create OpenGL context
    _glContext = SDL_GL_CreateContext(_handle);
    if (!_glContext)
    {
        String error_msg = String("Failed to create OpenGL context: ") + SDL_GetError();
        throw std::exception(error_msg.c_str());
    }
}
BOUNT_WINDOW_API void Subsystem_::onShutdown() noexcept
{
    if (_glContext)
    {
        SDL_GL_DestroyContext(_glContext);
        _glContext = nullptr;
    }
    if (_handle)
    {
        SDL_DestroyWindow(_handle);
        _handle = nullptr;
    }
}

BOUNT_WINDOW_API void Subsystem_::show() noexcept
{
    SDL_ShowWindow(_handle);
}
BOUNT_WINDOW_API void Subsystem_::hide() noexcept
{
    SDL_HideWindow(_handle);
}

BOUNT_WINDOW_API void Subsystem_::swap() noexcept
{
    SDL_GL_SwapWindow(_handle);
}

BOUNT_WINDOW_API GL::LayerGroup& Subsystem_::getLayers() noexcept
{
    return _layers;
}

BOUNT_WINDOW_API SDL_Window* const Subsystem_::getSDLHandle() const noexcept
{
    return _handle;
}
BOUNT_WINDOW_API SDL_GLContext const Subsystem_::getGLContext() const noexcept
{
    return _glContext;
}
}