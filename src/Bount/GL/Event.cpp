#include "Bount/GL/Event.hpp"

namespace Bount::GL
{
BOUNT_GL_API Event::Event(const SDL_Event& event)
    : _event(event)
    , _handled(0)
{
}
BOUNT_GL_API const SDL_Event& Event::getSDLEvent() const
{
    return _event;
}    
BOUNT_GL_API void Event::handle()
{
    if (_handled == UINT8_MAX) return;
    _handled++;
}
BOUNT_GL_API uint8_t Event::handled() const
{
    return _handled;
}
}