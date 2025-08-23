#include <cgl/core/rendercontext.h>

CGL::RenderContext::RenderContext()
{
    m_primitiveMap[Point] = GL_POINTS;
    m_primitiveMap[Line] = GL_LINES;
    m_primitiveMap[LineAdjency] = GL_LINES_ADJACENCY;
    m_primitiveMap[LineStrip] = GL_LINE_STRIP;
    m_primitiveMap[LineStripAdjency] = GL_LINE_STRIP_ADJACENCY;
    m_primitiveMap[LineLoop] = GL_LINE_LOOP;
    m_primitiveMap[Triangle] = GL_TRIANGLES;
    m_primitiveMap[TriangleStrip] = GL_TRIANGLE_STRIP;
    m_primitiveMap[TriangleStripAdjency] = GL_TRIANGLES_ADJACENCY;
    m_primitiveMap[TriangleFan] = GL_TRIANGLE_FAN;
}

void CGL::RenderContext::setPolygoneMode(int mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void CGL::RenderContext::render(const PrimitiveData &data)
{
    switch (data.drawType) {
        case CGL::RenderContext::Elements: {
            glDrawArrays(m_primitiveMap.at(data.type), data.offset, data.size);
        } break;
        case CGL::RenderContext::Indexes: {
            glDrawElements(m_primitiveMap.at(data.type), data.size, GL_UNSIGNED_INT, (void*)(size_t(data.offset)));
        } break;
        default: break;
    }
}

CGL::RenderContext& CGL::RenderContext::instance()
{
    static RenderContext context;
    return context;
}
