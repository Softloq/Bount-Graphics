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

EventManager* EventManager::_instance = nullptr;
std::once_flag EventManager::_init;

BOUNT_GL_API EventManager& EventManager::instance()
{
    std::call_once(_init, []()
    {
        _instance = new EventManager;
    });
    return *_instance;
}

BOUNT_GL_API EventManager::EventManager()
{

}
BOUNT_GL_API EventManager::~EventManager()
{
    
}

BOUNT_GL_API void EventManager::bind(DispatcherAddr addr, const std::string& action, const Callback& callback)
{
    if (!_dispatchers.contains(addr)) return;
    _dispatchers[addr][action].push_back(callback);
}

BOUNT_GL_API size_t EventManager::DispatcherAddrHash::operator()(DispatcherAddr addr) const
{
    return std::hash<uintptr_t>{}(reinterpret_cast<uintptr_t>(addr));
}
BOUNT_GL_API bool EventManager::DispatcherAddrEqual::operator()(DispatcherAddr addr1, DispatcherAddr addr2) const
{
    return addr1 == addr2;
}

BOUNT_GL_API EventDispatcher::EventDispatcher(EventManager::DispatcherAddr addr)
    : _addr(addr)
{
    EventManager::instance()._dispatchers[addr].clear();
}
BOUNT_GL_API EventDispatcher::~EventDispatcher()
{
    EventManager::instance()._dispatchers.erase(_addr);
}
BOUNT_GL_API void EventDispatcher::fire(const std::string& action, const Event& event)
{
    for (auto& event_callback : EventManager::instance()._dispatchers[_addr][action])
    {
        event_callback(event);
    }
}
}