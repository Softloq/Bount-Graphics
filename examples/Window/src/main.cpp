#include <Bount/Subsystem/Generic.hpp>

import Bount.Graphics.Subsystem;

using namespace Bount;

int main(int argc, char* argv[])
{
    Graphics::Subsystem::getInstance().startup();
    Graphics::Subsystem::getInstance().runGameLoop();
    Graphics::Subsystem::getInstance().shutdown();

    return 0;
}