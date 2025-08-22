#include <cgl/core/buffer/vaobuffer.h>
#include <glad/glad.h>
#include <cgl/utility/logger.h>

CGL::VAOBuffer::VAOBuffer()
{
    CGL_CheckErros();
}

void CGL::VAOBuffer::init()
{
    CGL_CheckErros();
    glGenVertexArrays(1, &m_vao);
    CGL_CheckErros();
    glGenBuffers(1, &m_vbo);
    CGL_CheckErros();
    glGenBuffers(1, &m_ebo);
    CGL_CheckErros();
}

CGL::VAOBuffer::~VAOBuffer()
{
    // std::cout << "VAO destruct begin" << std::endl;
    // std::cout << "vao: " << m_vao << std::endl;
    // std::cout << "vbo: " << m_vbo << std::endl;
    // std::cout << "ebo: " << m_ebo << std::endl;
    // glDeleteVertexArrays(1, &m_vao);
    // glDeleteBuffers(1, &m_vbo);
    // glDeleteBuffers(1, &m_ebo);
    // std::cout << "VAO destruct end" << std::endl;
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
