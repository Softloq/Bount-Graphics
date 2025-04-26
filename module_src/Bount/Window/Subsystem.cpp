#include "Bount/Window/Precompiled.hpp"
#include "Bount/Subsystem/Generic.hpp"

import Bount.Window.Subsystem;
import Bount.Graphics.Layer;
import Bount.Subsystem;

using namespace Bount;

BOUNT_WINDOW_API Window::Subsystem& Singleton::Generic<Window::Subsystem>::getInstance() noexcept { BOUNT_SINGLETON_GET_INSTANCE_IMPL(Window::Subsystem); }

namespace Bount::Window
{
Subsystem::Subsystem() noexcept
    : _handle(nullptr)
    , _glContext(nullptr)
{
}

Subsystem::~Subsystem() noexcept
{
}
    
void Subsystem::onStartup()
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
void Subsystem::onShutdown() noexcept
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

void Subsystem::show() noexcept
{
    SDL_ShowWindow(_handle);
}
void Subsystem::hide() noexcept
{
    SDL_HideWindow(_handle);
}

void Subsystem::swap() noexcept
{
    SDL_GL_SwapWindow(_handle);
}

Graphics::LayerGroup& Subsystem::getLayers() noexcept
{
    return _layers;
}

SDL_Window* const Subsystem::getSDLHandle() const noexcept
{
    return _handle;
}
SDL_GLContext const Subsystem::getGLContext() const noexcept
{
    return _glContext;
}
}