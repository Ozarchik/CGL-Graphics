#include "rectangle.h"

CGL::Rectangle::Rectangle()
    : Mesh(), m_vertexBuffer(vertices)
{
}

CGL::Rectangle::Rectangle(const CGL::TextureBase& texture)
    : Mesh(), m_vertexBuffer(vertices)
{
    m_buffer.textures.push_back(texture);
}

void CGL::Rectangle::draw(Shader& shader)
{
    m_vertexBuffer.use();
    if (m_buffer.textures.size()) {
        glBindTexture(GL_TEXTURE_2D, m_buffer.textures[0].id);
    }
    glDrawArrays(m_primitiveType, 0, 6);
    glDrawArraysInstanced(m_primitiveType, 0, 6, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
}
