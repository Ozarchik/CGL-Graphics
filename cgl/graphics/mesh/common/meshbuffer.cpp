#include <cgl/graphics/shader.h>
#include <cgl/graphics/mesh/common/meshbuffer.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <cgl/utility/logger.h>
#include <glad/glad.h>
#include <iostream>
#include <cgl/tools/backtrace/backtrace.h>

CGL::MeshBuffer::MeshBuffer()
{
}


CGL::MeshBuffer::MeshBuffer(const std::vector<CGL::Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices)
{
    
    m_vao = CGL::VAOBufferBuilder::build()
              .setVertexData(vertices.data(), vertices.size() * sizeof(CGL::Vertex), RenderContext::DrawChangeMode::Static)
              .setIndexData(indices.data(), indices.size() * sizeof(unsigned int), RenderContext::DrawChangeMode::Static)
              .setAttribute(0, 3, sizeof(CGL::Vertex), 0)
              .setAttribute(1, 3, sizeof(CGL::Vertex), offsetof(CGL::Vertex, normal))
              .setAttribute(2, 2, sizeof(CGL::Vertex), offsetof(CGL::Vertex, texcoord))
              .setAttribute(3, 3, sizeof(CGL::Vertex), offsetof(CGL::Vertex, color))
              .done();

    

    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);

    // glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(CGL::Vertex), vertices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, normal));
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, texcoord));
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(CGL::Vertex), (void*)offsetof(CGL::Vertex, color));

    // glBindVertexArray(0);
}

CGL::MeshBuffer::~MeshBuffer()
{
    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
    // glDeleteBuffers(1, &ebo);
}

void CGL::MeshBuffer::bind(CGL::Shader* shader)
{
    m_vao.bind();
}

void CGL::MeshBuffer::unbind()
{
    m_vao.unbind();
}

void CGL::MeshBuffer::setVAO(VAOBuffer&& vao)
{
    m_vao = std::move(vao);
}
