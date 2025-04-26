module;

#include "Bount/Event/Dispatcher.hpp"

export module Bount.Event.Dispatcher;
export import Bount.Event.Manager;

export namespace Bount::Event
{
class Dispatcher
{
    Manager::DispatcherAddr _addr;

public:
    BOUNT_EVENT_API Dispatcher(Manager::DispatcherAddr addr);
    BOUNT_EVENT_API ~Dispatcher();

    BOUNT_EVENT_API void fire(const String& action, const Base& event);
};
}
