#include <Bount/GL/Subsystem.hpp>

#include <iostream>

using namespace Bount;

int main(int argc, char* argv[])
{
    GL::Subsystem::getInstance().startup();
    GL::Subsystem::getInstance().runGameLoop();
    GL::Subsystem::getInstance().shutdown();

    return 0;
}