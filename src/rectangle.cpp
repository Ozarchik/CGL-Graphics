#include "rectangle.h"

CGL::Rectangle::Rectangle()
    : Mesh(), m_vertexBuffer(vertices)
{
}

CGL::Rectangle::Rectangle(const CGL::TextureBase& texture)
    : Mesh(), m_vertexBuffer(vertices)
{
    m_texureBuffer.m_id = texture.id;
}

void CGL::Rectangle::draw(Shader& shader)
{
    m_vertexBuffer.use();
    glBindTexture(GL_TEXTURE_2D, m_texureBuffer.m_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
}
