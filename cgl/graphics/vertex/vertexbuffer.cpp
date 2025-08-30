#include <cgl/graphics/vertex/vertexbuffer.h>
#include <glad/glad.h>

cgl::VertexBuffer::VertexBuffer(const std::vector<cgl::Vertex> &vertices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(cgl::Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, texcoord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, color));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void cgl::VertexBuffer::use()
{
    glBindVertexArray(vao);
}

void cgl::VertexBuffer::done()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
