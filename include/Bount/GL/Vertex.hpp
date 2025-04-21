#ifndef BOUNT_GL_VERTEX_HPP
#define BOUNT_GL_VERTEX_HPP

#include "Bount/GL/StandardMacros.hpp"

#include <glm/glm.hpp>

namespace Bount::GL
{
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};
}

#endif