#include "Bount/Event/Precompiled.hpp"
#include "Bount/Event/Base.hpp"

import Bount.Event.Base;

namespace Bount::Event
{
Base::Base(const SDL_Event& event)
    : _event(event)
    , _handled(0)
{
}
const SDL_Event& Base::getSDLEvent() const
{
    return _event;
}    
void Base::handle()
{
    if (_handled == UINT8_MAX) return;
    _handled++;
}

U8 Base::handled() const
{
    return _handled;
}
}