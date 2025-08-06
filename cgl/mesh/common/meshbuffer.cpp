#include <cgl/shader.h>
#include <cgl/mesh/common/meshbuffer.h>

#include <glad/glad.h>

CGL::MeshBuffer::MeshBuffer(const std::vector<CGL::Vertex> &vertices, const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, color));

    glBindVertexArray(0);
}

void CGL::MeshBuffer::bind(CGL::Shader* shader)
{
    glBindVertexArray(vao);
}

void CGL::MeshBuffer::unbind()
{
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
