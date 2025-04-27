
#include "Bount/Event/Precompiled.hpp"
#include "Bount/Event/Manager.hpp"

import Bount.Event.Manager;

namespace Bount::Event
{
Manager* Manager::_instance = nullptr;
std::once_flag Manager::_init;

Manager& Manager::instance()
{
    std::call_once(_init, []()
    {
        _instance = new Manager;
    });
    return *_instance;
}

Manager::Manager()
{

}
Manager::~Manager()
{
    
}

void Manager::bind(DispatcherAddr addr, const std::string& action, const Callback& callback)
{
    if (!_dispatchers.contains(addr)) return;
    _dispatchers[addr][action].push_back(callback);
}

size_t Manager::DispatcherAddrHash::operator()(DispatcherAddr addr) const
{
    return std::hash<uintptr_t>{}(reinterpret_cast<uintptr_t>(addr));
}
bool Manager::DispatcherAddrEqual::operator()(DispatcherAddr addr1, DispatcherAddr addr2) const
{
    return addr1 == addr2;
}
}