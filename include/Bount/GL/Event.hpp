#ifndef BOUNT_GL_EVENT_HPP
#define BOUNT_GL_EVENT_HPP

#include "Bount/GL/Lib-Macro.hpp"

#include <SDL3/SDL_events.h>

namespace Bount::GL
{
class Event
{
    SDL_Event _event;
    uint8_t _handled;

public:
    BOUNT_GL_API Event(const SDL_Event& event);

    BOUNT_GL_API const SDL_Event& getSDLEvent() const;
    
    BOUNT_GL_API void handle();
    BOUNT_GL_API uint8_t handled() const;
};
}

#endif