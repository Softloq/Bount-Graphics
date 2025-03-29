#include "Bount/GL/Precompiled.hpp"
#include "Bount/GL/System.hpp"

namespace Bount::GL
{
System* System::_instance = nullptr;
std::once_flag System::_init;
BOUNT_GL_API System& System::instance()
{
    std::call_once(_init, []()
    {
        _instance = new System;
    });
    return *_instance;
}
BOUNT_GL_API System::System()
{
}
BOUNT_GL_API System::~System()
{
}
BOUNT_GL_API bool System::initialize()
{
    return true;
}
BOUNT_GL_API void System::shutdown()
{

}
}