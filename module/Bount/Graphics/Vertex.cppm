module;

#include "Bount/Graphics/StandardMacros.hpp"

#include <glm/glm.hpp>

export module Bount.Graphics.Vertex;
export namespace Bount::Graphics
{
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};
}
