#include <cgl/graphics/mesh/2D/rectangle.h>

cgl::Rectangle::Rectangle()
    : Mesh(), m_vertexBuffer(vertices)
{
    m_primitiveData.drawType = cgl::DrawType::Elements;
    m_primitiveData.type = cgl::Primitive::Triangle;
    m_primitiveData.size = 6;
    m_primitiveData.offset = 0;

}

cgl::Rectangle::Rectangle(glm::vec3 color)
    : Mesh(), m_color(color), m_vertexBuffer(vertices)
{

}

void cgl::Rectangle::draw(Shader& shader)
{
    shader.use();
    m_vertexBuffer.use();
    cgl::RenderContext::instance().render(m_primitiveData);
    m_vertexBuffer.done();
    shader.done();
}
