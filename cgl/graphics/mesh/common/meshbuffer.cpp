#include <cgl/graphics/shader.h>
#include <cgl/graphics/mesh/common/meshbuffer.h>

#include <glad/glad.h>

CGL::MeshBuffer::MeshBuffer()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}


CGL::MeshBuffer::MeshBuffer(const std::vector<CGL::Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

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

CGL::MeshBuffer::~MeshBuffer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void CGL::MeshBuffer::bind(CGL::Shader* shader)
{
    glBindVertexArray(vao);
}

void CGL::MeshBuffer::unbind()
{
    glBindVertexArray(0);
}

void CGL::MeshBuffer::setVertices(const std::vector<Vertex> &vertices)
{
    m_vertices = vertices;

    bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, color));

    unbind();
}

void CGL::MeshBuffer::setIndices(const std::vector<unsigned int> &indices)
{    
    m_indices = indices;

    bind();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    unbind();
}
