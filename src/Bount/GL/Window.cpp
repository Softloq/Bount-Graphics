#include "Bount/GL/Window.hpp"

#include <SDL3/SDL.h>
#include <GL/glew.h>

#include <iostream>

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
    , _sdl_init(false)
    , _running(false)
{

}
BOUNT_GL_API Window::~Window()
{

}
    
BOUNT_GL_API bool Window::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    _sdl_init = true;

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create SDL window
    _handle = SDL_CreateWindow("Bount: Underdogs Triump Together!", 800, 600, SDL_WINDOW_OPENGL);
    if (!_handle)
    {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        close();
        return false;
    }
    SDL_HideWindow(_handle);

    // Create OpenGL context
    _glContext = SDL_GL_CreateContext(_handle);
    if (!_glContext)
    {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        close();
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        close();
        return false;
    }

    std::cout << "Initialized SDL Window" << std::endl;
}

BOUNT_GL_API void Window::run()
{

}

BOUNT_GL_API void Window::show()
{   SDL_ShowWindow(_handle);

}
BOUNT_GL_API void Window::hide()
{
    SDL_HideWindow(_handle);
}

BOUNT_GL_API void Window::close()
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
    if (_sdl_init)
    {
        SDL_Quit();
        _sdl_init = false;
    }
}
}