#include <cgl/graphics/mesh/2D/line.h>

cgl::Line::Line()
    : Mesh()
{
    m_primitiveData.drawType = cgl::RenderContext::Elements;
    m_primitiveData.type = cgl::RenderContext::Line;
    m_primitiveData.size = 4;
    m_primitiveData.offset = 0;
}

void cgl::Line::draw(Shader &shader)
{
    shader.use();
    m_buffer.bind();
    RenderContext::instance().render(m_primitiveData);
    m_buffer.unbind();
    shader.done();
}


