#include "Bount/Graphics/Precompiled.hpp"

import Bount.Graphics.Layer;
import Bount.Event.Base;

namespace Bount::Graphics
{
Layer::~Layer()
{
}

void Layer::handleEvent(const Event::Base& event)
{
}
void Layer::draw()
{
}

void LayerGroup::handleEvent(const Event::Base& event)
{
    for (auto it = _layers.rbegin(); it != _layers.rend(); ++it) if (!event.handled()) (*it)->handleEvent(event);
}
void LayerGroup::draw()
{
    for (auto it = _layers.begin(); it != _layers.end(); ++it) (*it)->draw();
}

std::shared_ptr<Layer>& LayerGroup::front()
{
    return _layers.front();
}
std::shared_ptr<Layer>& LayerGroup::back()
{
    return _layers.back();
}
void LayerGroup::append(const std::shared_ptr<Layer>& layer)
{
    _layers.push_back(layer);
}
void LayerGroup::prepend(const std::shared_ptr<Layer>& layer)
{
    _layers.push_front(layer);
}
void LayerGroup::popFront()
{
    _layers.pop_front();
}
void LayerGroup::popBack()
{
    _layers.pop_back();
}
}
