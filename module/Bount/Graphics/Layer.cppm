module;

#include "Bount/Graphics/StandardMacros.hpp"

#include <list>
#include <memory>

export module Bount.Graphics.Layer;
import Bount.Event.Base;
export namespace Bount::Graphics
{
class Layer
{
public:
    BOUNT_GRAPHICS_API virtual ~Layer() = 0;

    BOUNT_GRAPHICS_API virtual void handleEvent(const Event::Base& event);
    BOUNT_GRAPHICS_API virtual void draw();
};

class LayerGroup : Layer
{
    std::list<std::shared_ptr<Layer>> _layers;

public:
    BOUNT_GRAPHICS_API void handleEvent(const Event::Base& event) override;
    BOUNT_GRAPHICS_API void draw() override;
    
    BOUNT_GRAPHICS_API std::shared_ptr<Layer>& front();
    BOUNT_GRAPHICS_API std::shared_ptr<Layer>& back();
    BOUNT_GRAPHICS_API void append(const std::shared_ptr<Layer>& layer);
    BOUNT_GRAPHICS_API void prepend(const std::shared_ptr<Layer>& layer);
    BOUNT_GRAPHICS_API void popFront();
    BOUNT_GRAPHICS_API void popBack();
};
}
