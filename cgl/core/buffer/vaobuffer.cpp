#include <cgl/core/buffer/vaobuffer.h>
#include <glad/glad.h>
#include <cgl/utility/logger.h>

CGL::VAOBuffer::VAOBuffer()
{
}

void CGL::VAOBuffer::init()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

CGL::VAOBuffer::~VAOBuffer()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void CGL::VAOBuffer::reset()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

CGL::VAOBuffer::VAOBuffer(VAOBuffer &&other) noexcept
    : m_vao(other.m_vao)
    , m_vbo(other.m_vbo)
    , m_ebo(other.m_ebo)
{
    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;
}

CGL::VAOBuffer &CGL::VAOBuffer::operator=(VAOBuffer &&other) noexcept
{
    if (m_vao)
        glDeleteVertexArrays(1, &m_vao);

    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;

    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;

    return *this;
}

unsigned int CGL::VAOBuffer::id()
{
    return m_vao;
}

void CGL::VAOBuffer::bind()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void CGL::VAOBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CGL::VAOBuffer::setVertexData(const void *data, int size, bool staticDraw)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    unbind();
}

void CGL::VAOBuffer::setIndexData(const void *data, int size, bool staticDraw)
{
    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    unbind();
}

void CGL::VAOBuffer::setAttribute(int index, int components, int stride, int offset)
{
    bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    unbind();
}
