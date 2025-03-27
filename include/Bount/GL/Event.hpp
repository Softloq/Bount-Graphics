#ifndef BOUNT_GL_EVENT_HPP
#define BOUNT_GL_EVENT_HPP

#include "Bount/GL/Lib-Macro.hpp"

#include <SDL3/SDL_events.h>

#include <unordered_map>
#include <functional>
#include <list>
#include <mutex>

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
class EventManager
{
    static EventManager* _instance;
    static std::once_flag _init;

public:
    BOUNT_GL_API EventManager(const EventManager&) = delete;
    BOUNT_GL_API EventManager& operator=(const EventManager&) = delete;

    BOUNT_GL_API static EventManager& instance();

private:
    BOUNT_GL_API EventManager();
    BOUNT_GL_API ~EventManager();

public:
    typedef std::function<void (const Event& event)> Callback;
    typedef void* const DispatcherAddr;
    friend class EventDispatcher;
    
    BOUNT_GL_API void bind(DispatcherAddr addr, const std::string& action, const Callback& callback);

private:
    typedef std::list<Callback> Callbacks;
    typedef std::unordered_map<std::string, Callbacks> ActionMap;

    struct DispatcherAddrHash
    {
        BOUNT_GL_API size_t operator()(DispatcherAddr addr) const;
    };
    struct DispatcherAddrEqual
    {
        BOUNT_GL_API bool operator()(DispatcherAddr addr1, DispatcherAddr addr2) const;
    };
    std::unordered_map<DispatcherAddr, ActionMap, DispatcherAddrHash, DispatcherAddrEqual> _dispatchers;
};

class EventDispatcher
{
    EventManager::DispatcherAddr _addr;

public:
    BOUNT_GL_API EventDispatcher(EventManager::DispatcherAddr addr);
    BOUNT_GL_API ~EventDispatcher();

    BOUNT_GL_API void fire(const std::string& action, const Event& event);
};
}

#endif