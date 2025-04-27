#include "Bount/Graphics/Precompiled.hpp"

import Bount.Graphics.Mesh;

namespace Bount::Graphics
{
Mesh::Mesh()
{
    glGenVertexArrays(1, &_glVAO);
    glGenBuffers(1, &_glVBO);
    glGenBuffers(1, &_glEBO);
}
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_glVAO);
    glDeleteBuffers(1, &_glVBO);
    glDeleteBuffers(1, &_glEBO);
}

void Mesh::addVertices(const std::vector<Vertex>& vertices)
{
    _vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
}
void Mesh::addIndices(const std::vector<U32>& indices)
{
    _indices.insert(_indices.end(), indices.begin(), indices.end());
}

void Mesh::update()
{
    glBindVertexArray(_glVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _glVBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(U32), _indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
}
void Mesh::draw()
{
    glBindVertexArray(_glVAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
}
