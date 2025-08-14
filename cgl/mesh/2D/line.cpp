#include <cgl/mesh/2D/line.h>

CGL::Line::Line()
    : Mesh()
{
    m_primitiveData.drawType = CGL::RenderContext::Elements;
    m_primitiveData.type = CGL::RenderContext::Line;
    m_primitiveData.size = 4;
    m_primitiveData.offset = 0;
}

void CGL::Line::draw(Shader &shader)
{
    shader.use();
    m_buffer.bind();
    RenderContext::instance().render(m_primitiveData);
    m_buffer.unbind();
    shader.done();
}


