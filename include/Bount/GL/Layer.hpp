#ifndef BOUNT_GL_LAYER_HPP
#define BOUNT_GL_LAYER_HPP

#include "Bount/GL/Event.hpp"

#include <list>
#include <memory>

namespace Bount::GL
{
class Layer
{
public:
    BOUNT_GL_API virtual ~Layer() = 0;

    BOUNT_GL_API virtual void handleEvent(const Event& event);
    BOUNT_GL_API virtual void draw();
};

class LayerGroup : Layer
{
    std::list<std::shared_ptr<Layer>> _layers;

public:
    BOUNT_GL_API void handleEvent(const Event& event) override;
    BOUNT_GL_API void draw() override;
    
    BOUNT_GL_API std::shared_ptr<Layer>& front();
    BOUNT_GL_API std::shared_ptr<Layer>& back();
    BOUNT_GL_API void append(const std::shared_ptr<Layer>& layer);
    BOUNT_GL_API void prepend(const std::shared_ptr<Layer>& layer);
    BOUNT_GL_API void popFront();
    BOUNT_GL_API void popBack();
};
}

#endif