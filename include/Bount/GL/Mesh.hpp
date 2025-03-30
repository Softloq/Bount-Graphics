#ifndef BOUNT_GL_MESH_HPP
#define BOUNT_GL_MESH_HPP

#include "Bount/GL/Lib-Macro.hpp"
#include "Bount/GL/Vertex.hpp"
#include <vector>

namespace Bount::GL
{
class Mesh
{
    std::vector<Vertex> _vertices;
    std::vector<U32> _indices;
    GLuint _glVAO;
    GLuint _glVBO;
    GLuint _glEBO;

public:
    BOUNT_GL_API Mesh();
    BOUNT_GL_API ~Mesh();

    BOUNT_GL_API void addVertices(const std::vector<Vertex>& vertices);
    BOUNT_GL_API void addIndices(const std::vector<U32>& indices);

    BOUNT_GL_API void update();
    BOUNT_GL_API void draw();
};
}

#endif