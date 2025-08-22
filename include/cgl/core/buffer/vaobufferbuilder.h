#ifndef CGL_VAOBUFFERBUILDER_H
#define CGL_VAOBUFFERBUILDER_H

#include <cgl/core/buffer/vaobuffer.h>

namespace CGL {
class VAOBufferBuilder
{
public:
    static VAOBufferBuilder build();

    VAOBufferBuilder& setVertexData(const void* data, int size, bool staticDraw);
    VAOBufferBuilder& setIndexData(const void* data, int size, bool staticDraw);
    VAOBufferBuilder& setAttribute(int index, int components, int stride, int offset);
    VAOBuffer done();

private:
    VAOBufferBuilder();

private:
    VAOBuffer m_vao;
};
}

#endif // CGL_VAOBUFFERBUILDER_H
