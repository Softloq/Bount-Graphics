module;

#include "Bount/Graphics/StandardMacros.hpp"
#include <vector>

export module Bount.Graphics.Mesh;
import Bount.Graphics.Vertex;
export namespace Bount::Graphics
{
class Mesh
{
    std::vector<Vertex> _vertices;
    std::vector<U32> _indices;
    GLuint _glVAO;
    GLuint _glVBO;
    GLuint _glEBO;

public:
    BOUNT_GRAPHICS_API Mesh();
    BOUNT_GRAPHICS_API ~Mesh();

    BOUNT_GRAPHICS_API void addVertices(const std::vector<Vertex>& vertices);
    BOUNT_GRAPHICS_API void addIndices(const std::vector<U32>& indices);

    BOUNT_GRAPHICS_API void update();
    BOUNT_GRAPHICS_API void draw();
};
}
