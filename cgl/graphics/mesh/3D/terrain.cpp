#include <cgl/graphics/mesh/3D/terrain.h>
#include <cgl/utility/logger.h>

CGL::Terrain::Terrain()
    : Mesh()
{
}

void CGL::Terrain::draw(Shader &shader)
{
    shader.use();
    
    m_buffer.bind();

    
    CGL::PrimitiveData toDraw = m_primitiveData;
    m_primitiveData.offset = 5248;
    m_primitiveData.size = 1755;
    toDraw.size = m_primitiveData.offset;
    // int vertices = 5248;
    // int nums = 1755;
    // std::swap(vertices, nums);
    // toDraw.size = vertices;

    
    // CGL::RenderContext::instance().setPolygoneMode(GL_LINE);

    // for (unsigned int strip = 0; nums; ++strip) {
    //     toDraw.offset = sizeof(unsigned int) * vertices * strip;

    //     CGL::RenderContext::instance().render(toDraw);
    // }
    for (unsigned int strip = 0; strip < m_primitiveData.size; ++strip) {
        toDraw.offset = sizeof(unsigned int) * m_primitiveData.offset * strip;

        CGL::RenderContext::instance().render(toDraw);
    }

    // CGL::RenderContext::instance().setPolygoneMode(GL_FILL);

    

    m_buffer.unbind();
    shader.done();
}
