#include <cgl/graphics/mesh/2D/rectangle.h>

CGL::Rectangle::Rectangle()
    : Mesh(), m_vertexBuffer(vertices)
{
    m_primitiveData.drawType = CGL::RenderContext::Elements;
    m_primitiveData.type = CGL::RenderContext::Triangle;
    m_primitiveData.size = 6;
    m_primitiveData.offset = 0;

}

CGL::Rectangle::Rectangle(glm::vec3 color)
    : Mesh(), m_color(color), m_vertexBuffer(vertices)
{

}

void CGL::Rectangle::draw(Shader& shader)
{
    shader.use();
    m_vertexBuffer.use();
    CGL::RenderContext::instance().render(m_primitiveData);
    m_vertexBuffer.done();
    shader.done();
}
