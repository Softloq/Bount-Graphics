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

BOUNT_GL_API std::shared_ptr<Layer>& LayerGroup::front()
{
    return _layers.front();
}
BOUNT_GL_API std::shared_ptr<Layer>& LayerGroup::back()
{
    return _layers.back();
}
BOUNT_GL_API void LayerGroup::append(const std::shared_ptr<Layer>& layer)
{
    _layers.push_back(layer);
}
BOUNT_GL_API void LayerGroup::prepend(const std::shared_ptr<Layer>& layer)
{
    _layers.push_front(layer);
}
BOUNT_GL_API void LayerGroup::popFront()
{
    _layers.pop_front();
}
BOUNT_GL_API void LayerGroup::popBack()
{
    _layers.pop_back();
}
}