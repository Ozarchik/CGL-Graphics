#include <cgl/mesh/2D/rectangle.h>

CGL::Rectangle::Rectangle()
    : Mesh(), m_vertexBuffer(vertices)
{
}

CGL::Rectangle::Rectangle(glm::vec3 color)
    : Mesh(), m_color(color), m_vertexBuffer(vertices)
{

}

void CGL::Rectangle::draw(Shader& shader)
{
    m_vertexBuffer.use();
    glDrawArrays(m_primitiveType, 0, 6);
    glDrawArraysInstanced(m_primitiveType, 0, 6, 4);
    m_vertexBuffer.done();
}
