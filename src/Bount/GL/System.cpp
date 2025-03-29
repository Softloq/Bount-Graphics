#include "Bount/GL/Precompiled.hpp"
#include "Bount/GL/System.hpp"
#include "Bount/GL/Window.hpp"

namespace Bount::GL
{
System* System::_instance = nullptr;
std::once_flag System::_init;
BOUNT_GL_API System& System::instance()
{
    std::call_once(_init, []()
    {
        _instance = new System;
    });
    return *_instance;
}
BOUNT_GL_API System::System()
    : _sdl_init(false)
    , _running(false)
{
}
BOUNT_GL_API System::~System()
{
}
BOUNT_GL_API bool System::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    _sdl_init = true;

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if (!Window::instance().initialize())
    {
        shutdown();
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        shutdown();
        return false;
    }

    return true;
}
BOUNT_GL_API void System::shutdown()
{
    Window::instance().shutdown();
    if (_sdl_init)
    {
        SDL_Quit();
        _sdl_init = false;
    }
}

BOUNT_GL_API void System::game_loop()
{
    if (_running) return;
    _running = true;
    Window::instance().show();

    SDL_Event sdl_event;
    while (_running) 
    {
        while (SDL_PollEvent(&sdl_event))
        {
            Event event(sdl_event);
            Window::instance().getLayers().handleEvent(event);
            if (event.handled()) continue;
            
            if (sdl_event.type == SDL_EVENT_QUIT)
            {
                _running = false;
            }
        }

        // Clear screen with a color
        glClearColor(0.125f, 0.375f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Window::instance().getLayers().draw();
        Window::instance().swap();
    }

    _running = false;

}
}