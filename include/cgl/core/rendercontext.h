#ifndef CGL_RENDERCONTEXT_H
#define CGL_RENDERCONTEXT_H

#include <cgl/core/corecontext.h>
#include <unordered_map>

namespace CGL {

struct PrimitiveData;

class RenderContext
{
public:
    enum DrawType {
        Elements,
        Indexes
    };

    enum Primitive {
        Point = GL_POINTS,
        Line = GL_LINES,
        LineAdjency = GL_LINES_ADJACENCY,
        LineStrip = GL_LINE_STRIP,
        LineStripAdjency = GL_LINE_STRIP_ADJACENCY,
        LineLoop = GL_LINE_LOOP,
        Triangle = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleStripAdjency = GL_TRIANGLES_ADJACENCY,
        TriangleFan = GL_TRIANGLE_FAN,
    };

    void render(const PrimitiveData& data);

    static RenderContext& instance();

private:
    RenderContext();
    std::unordered_map<Primitive, int> m_primitiveMap;
};

struct PrimitiveData {
    PrimitiveData()
    : type(RenderContext::Primitive::Triangle)
    , drawType(RenderContext::DrawType::Elements)
    , offset(0)
    , size(0)
    {

    }
    RenderContext::Primitive type;
    RenderContext::DrawType drawType;
    int offset;
    int size;
};
}

#endif // CGL_RENDERCONTEXT_H
