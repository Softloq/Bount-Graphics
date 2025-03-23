#include "Bount/GL/Layer.hpp"

namespace Bount::GL
{
BOUNT_GL_API Layer::~Layer()
{
}

BOUNT_GL_API void Layer::handleEvent()
{
}
BOUNT_GL_API void Layer::draw()
{
}

BOUNT_GL_API void LayerGroup::handleEvent()
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); ++it) (*it)->handleEvent();
}
BOUNT_GL_API void LayerGroup::draw()
{
    for (auto it = _layers.begin(); it != _layers.end(); ++it) (*it)->draw();
}
}