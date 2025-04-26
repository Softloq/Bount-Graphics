module;

#include "Bount/Event/Base.hpp"

export module Bount.Event.Base;
export namespace Bount::Event
{
class Base
{
    SDL_Event _event;
    U8 _handled;

public:
    BOUNT_EVENT_API Base(const SDL_Event& event);

    BOUNT_EVENT_API const SDL_Event& getSDLEvent() const;
    
    BOUNT_EVENT_API void handle();
    BOUNT_EVENT_API U8 handled() const;
};
}
