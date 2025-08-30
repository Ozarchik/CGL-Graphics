#ifndef CGL_RENDERCONTEXT_H
#define CGL_RENDERCONTEXT_H

#include <cgl/core/corecontext.h>
#include <unordered_map>

namespace cgl {

enum class DrawType {
    Elements,
    Indexes
};

enum class DrawChangeMode {
    Static,
    Dynamic
};

enum class PolygoneMode {
    Fill,
    Lines
};

enum class Primitive {
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

struct PrimitiveData;

class RenderContext
{
public:
    void render(const PrimitiveData& data);

    static RenderContext& instance();
    
    void setPolygoneMode(const PolygoneMode &mode);

private:
    RenderContext();
    std::unordered_map<Primitive, int> m_primitiveMap;
};

struct PrimitiveData {
    PrimitiveData()
        : type(cgl::Primitive::Triangle)
        , drawType(cgl::DrawType::Elements)
        , offset(0)
        , size(0)
    {}

    PrimitiveData(cgl::Primitive _type, cgl::DrawType _drawType, int _size, int _offset)
        : type(_type)
        , drawType(_drawType)
        , size(_size)
        , offset(_offset)
    {}

    cgl::Primitive type;
    cgl::DrawType drawType;
    int offset;
    int size;
};

RenderContext& cglRenderContext();
}

#endif // CGL_RENDERCONTEXT_H
