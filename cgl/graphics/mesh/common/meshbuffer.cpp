#include <cgl/graphics/shader.h>
#include <cgl/graphics/mesh/common/meshbuffer.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <glad/glad.h>
#include <iostream>

cgl::MeshBuffer::MeshBuffer() {
    m_vao = std::make_unique<cgl::VAOBuffer>();
}

cgl::MeshBuffer::MeshBuffer(const std::vector<cgl::Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_vertices(vertices), m_indices(indices)
{
    
    m_vao = cgl::VAOBufferBuilder::build()
        .setVertexData(vertices.data(), vertices.size() * sizeof(cgl::Vertex), RenderContext::DrawChangeMode::Static)
        .setIndexData(indices.data(), indices.size() * sizeof(unsigned int), RenderContext::DrawChangeMode::Static)
        .setAttribute(0, 3, sizeof(cgl::Vertex), 0)
        .setAttribute(1, 3, sizeof(cgl::Vertex), offsetof(cgl::Vertex, normal))
        .setAttribute(2, 2, sizeof(cgl::Vertex), offsetof(cgl::Vertex, texcoord))
        .setAttribute(3, 3, sizeof(cgl::Vertex), offsetof(cgl::Vertex, color))
        .done();
    cglErrors();

    

    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);

    // glBindVertexArray(vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(cgl::Vertex), vertices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, normal));
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, texcoord));
    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(cgl::Vertex), (void*)offsetof(cgl::Vertex, color));

    // glBindVertexArray(0);
}

cgl::MeshBuffer::~MeshBuffer()
{
    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
    // glDeleteBuffers(1, &ebo);
}

void cgl::MeshBuffer::bind(cgl::Shader* shader)
{
    m_vao->bind();
}

void cgl::MeshBuffer::unbind()
{
    m_vao->unbind();
}

void cgl::MeshBuffer::setVAO(std::unique_ptr<VAOBuffer>&& vao) {
    // m_vao = std::move(vao);
    m_vao = std::move(vao);
}
