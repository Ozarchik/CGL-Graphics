#include <cgl/graphics/mesh/3D/terrain.h>
#include <iostream>

cgl::Terrain::Terrain()
    : Mesh()
{
}

void cgl::Terrain::draw(Shader &shader)
{
    shader.use();
    m_buffer.bind();

    cgl::PrimitiveData toDraw = m_primitiveData;
    toDraw.size = m_primitiveData.offset;

    // shader.setBool("line_polygone", false);
    // cglRenderContext().setPolygoneMode(GL_FILL);
    // for (unsigned int strip = 0; strip < m_primitiveData.size; ++strip) {
    //     toDraw.offset = sizeof(unsigned int) * m_primitiveData.offset * strip;
    //     cglRenderContext().render(toDraw);
    // }
    shader.setBool("line_polygone", true);
    shader.setVec3("line_color", glm::vec3(1.0));
    cglRenderContext().setPolygoneMode(RenderContext::PolygoneMode::Lines);
    for (unsigned int strip = 0; strip < m_primitiveData.size; ++strip) {
        toDraw.offset = sizeof(unsigned int) * m_primitiveData.offset * strip;
        cglRenderContext().render(toDraw);
    }

    m_buffer.unbind();
    shader.done();
}
