#include "Bount/Event/Precompiled.hpp"
#include "Bount/Event/Dispatcher.hpp"

import Bount.Event.Dispatcher;

namespace Bount::Event
{
Dispatcher::Dispatcher(Manager::DispatcherAddr addr)
    : _addr(addr)
{
    Manager::instance()._dispatchers[addr].clear();
}
Dispatcher::~Dispatcher()
{
    Manager::instance()._dispatchers.erase(_addr);
}
void Dispatcher::fire(const std::string& action, const Event::Base& event)
{
    for (auto& event_callback : Manager::instance()._dispatchers[_addr][action])
    {
        event_callback(event);
    }
}
}