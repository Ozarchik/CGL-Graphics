#include "vertexbuffer.h"
#include <glad/glad.h>

CGL::VertexBuffer::VertexBuffer(const std::vector<CGL::Vertex> &vertices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));

    glBindVertexArray(0);
}

void CGL::VertexBuffer::use()
{
    glBindVertexArray(VAO);
}
