#include "Bount/Graphics/Precompiled.hpp"
#include "Bount/Subsystem/Generic.hpp"

import Bount.Graphics.Subsystem;
import Bount.Window.Subsystem;
import Bount.Event.Base;
import Bount.Subsystem;

using namespace Bount;

BOUNT_GRAPHICS_API Graphics::Subsystem& Singleton::Generic<Graphics::Subsystem>::getInstance() noexcept { BOUNT_SINGLETON_GET_INSTANCE_IMPL(Graphics::Subsystem); }

namespace Bount::Graphics
{

Subsystem::Subsystem() noexcept
    : _initSDL(false)
    , _initGLEW(false)
    , _running(false)
{
}
Subsystem::~Subsystem() noexcept
{
}

void Subsystem::onStartup()
{
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        String error_msg = String("Failed to initialize SDL: ") + SDL_GetError();
        throw std::exception(error_msg.c_str());
    }
    _initSDL = true;

    // Set Default OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    Window::Subsystem::getInstance().startup();
    if (!Window::Subsystem::getInstance().hasStartedUp())
    {
        String error_msg = String("Failed to start the Window subsystem: ") + SDL_GetError();
        throw std::exception(error_msg.c_str());
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
        String error_msg = String("Failed to initialize GLEW: ") + (const char*)glewGetErrorString(glewErr);
        throw std::exception(error_msg.c_str());
    }
    _initGLEW = true;
}

void Subsystem::onShutdown() noexcept
{
    if (_initGLEW)
    {
        // No uninitialization needed.
        _initGLEW = false;
    }
    Window::Subsystem::getInstance().shutdown();
    if (_initSDL)
    {
        SDL_Quit();
        _initSDL = false;
    }
}

void Subsystem::runGameLoop() noexcept
{
    if (_running) return;
    _running = true;
    Window::Subsystem::getInstance().show();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);

    SDL_Event sdl_event;
    while (_running) 
    {
        while (SDL_PollEvent(&sdl_event))
        {
            Event::Base event(sdl_event);
            Window::Subsystem::getInstance().getLayers().handleEvent(event);
            if (event.handled()) continue;
            
            if (sdl_event.type == SDL_EVENT_QUIT)
            {
                _running = false;
            }
        }

        // Clear screen with a color
        glClearColor(0.125f, 0.375f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Window::Subsystem::getInstance().getLayers().draw();
        Window::Subsystem::getInstance().swap();
    }

    glDepthMask(GL_FALSE);
    glDisable(GL_BLEND);

    _running = false;
}
}
