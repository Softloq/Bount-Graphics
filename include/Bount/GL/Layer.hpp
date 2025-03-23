#ifndef BOUNT_GL_WINDOW_HPP
#define BOUNT_GL_WINDOW_HPP

#include "Bount/GL/Lib-Macro.hpp"

#include <list>
#include <memory>

namespace Bount::GL
{
class Layer
{
public:
    BOUNT_GL_API virtual ~Layer() = 0;

    BOUNT_GL_API virtual void handleEvent();
    BOUNT_GL_API virtual void draw();
};

class LayerGroup : Layer
{
    std::list<std::shared_ptr<Layer>> _layers;

public:
    BOUNT_GL_API void handleEvent() override;
    BOUNT_GL_API void draw() override;
};
}

#endif