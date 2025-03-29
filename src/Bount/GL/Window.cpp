#include "Bount/GL/Precompiled.hpp"
#include "Bount/GL/Window.hpp"

namespace Bount::GL
{
Window* Window::_instance = nullptr;
std::once_flag Window::_init;
BOUNT_GL_API Window& Window::instance()
{
    std::call_once(_init, []()
    {
        _instance = new Window;
    });
    return *_instance;
}

BOUNT_GL_API Window::Window()
    : _handle(nullptr)
    , _glContext(nullptr)
{

}
BOUNT_GL_API Window::~Window()
{

}
    
BOUNT_GL_API bool Window::initialize()
{
    // Create SDL window
    _handle = SDL_CreateWindow("Bount: Underdogs Triump Together!", 800, 600, SDL_WINDOW_OPENGL);
    if (!_handle)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        shutdown();
        return false;
    }
    SDL_HideWindow(_handle);

    // Create OpenGL context
    _glContext = SDL_GL_CreateContext(_handle);
    if (!_glContext)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        shutdown();
        return false;
    }
    return true;
}
BOUNT_GL_API void Window::shutdown()
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
BOUNT_GL_API void Window::run()
{
    
}

BOUNT_GL_API void Window::show()
{
    SDL_ShowWindow(_handle);
}
BOUNT_GL_API void Window::hide()
{
    SDL_HideWindow(_handle);
}

BOUNT_GL_API void Window::swap()
{
    SDL_GL_SwapWindow(_handle);
}

BOUNT_GL_API LayerGroup& Window::getLayers()
{
    return _layers;
}

BOUNT_GL_API SDL_Window* const Window::getSDLHandle() const
{
    return _handle;
}
BOUNT_GL_API SDL_GLContext const Window::getGLContext() const
{
    return _glContext;
}
}