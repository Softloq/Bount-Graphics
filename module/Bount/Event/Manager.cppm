module;

#include "Bount/Event/Manager.hpp"

export module Bount.Event.Manager;
export import Bount.Event.Base;

export namespace Bount::Event
{
class Manager
{
    static Manager* _instance;
    static std::once_flag _init;

public:
    BOUNT_EVENT_API Manager(const Manager&) = delete;
    BOUNT_EVENT_API Manager& operator=(const Manager&) = delete;

    BOUNT_EVENT_API static Manager& instance();

private:
    BOUNT_EVENT_API Manager();
    BOUNT_EVENT_API ~Manager();

public:
    typedef std::function<void (const Base& event)> Callback;
    typedef void* const DispatcherAddr;
    friend class Dispatcher;
    
    BOUNT_EVENT_API void bind(DispatcherAddr addr, const String& action, const Callback& callback);

private:
    typedef std::list<Callback> Callbacks;
    typedef std::unordered_map<String, Callbacks> ActionMap;

    struct DispatcherAddrHash
    {
        BOUNT_EVENT_API size_t operator()(DispatcherAddr addr) const;
    };
    struct DispatcherAddrEqual
    {
        BOUNT_EVENT_API Bool operator()(DispatcherAddr addr1, DispatcherAddr addr2) const;
    };
    std::unordered_map<DispatcherAddr, ActionMap, DispatcherAddrHash, DispatcherAddrEqual> _dispatchers;
};
}
