#include <cgl/core/rendercontext.h>

cgl::RenderContext::RenderContext()
{
    m_primitiveMap[cgl::Primitive::Point] = GL_POINTS;
    m_primitiveMap[cgl::Primitive::Line] = GL_LINES;
    m_primitiveMap[cgl::Primitive::LineAdjency] = GL_LINES_ADJACENCY;
    m_primitiveMap[cgl::Primitive::LineStrip] = GL_LINE_STRIP;
    m_primitiveMap[cgl::Primitive::LineStripAdjency] = GL_LINE_STRIP_ADJACENCY;
    m_primitiveMap[cgl::Primitive::LineLoop] = GL_LINE_LOOP;
    m_primitiveMap[cgl::Primitive::Triangle] = GL_TRIANGLES;
    m_primitiveMap[cgl::Primitive::TriangleStrip] = GL_TRIANGLE_STRIP;
    m_primitiveMap[cgl::Primitive::TriangleStripAdjency] = GL_TRIANGLES_ADJACENCY;
    m_primitiveMap[cgl::Primitive::TriangleFan] = GL_TRIANGLE_FAN;
    cglErrors();
}

void cgl::RenderContext::setPolygoneMode(const PolygoneMode& mode)
{
    switch (mode) {
    case PolygoneMode::Fill: {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } break;
    case PolygoneMode::Lines: {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } break;
    }

    cglErrors();
}

void cgl::RenderContext::render(const PrimitiveData &data)
{
    cglErrors();
    switch (data.drawType) {
        case cgl::DrawType::Elements: {
            glDrawArrays(m_primitiveMap.at(data.type), data.offset, data.size);
        } break;
        case cgl::DrawType::Indexes: {
            glDrawElements(m_primitiveMap.at(data.type), data.size, GL_UNSIGNED_INT, (void*)(size_t(data.offset)));
        } break;
        default: break;
    }
    cglErrors();
}

cgl::RenderContext& cgl::RenderContext::instance()
{
    static RenderContext context;
    return context;
}

cgl::RenderContext &cgl::cglRenderContext()
{
    return cgl::RenderContext::instance();
}
