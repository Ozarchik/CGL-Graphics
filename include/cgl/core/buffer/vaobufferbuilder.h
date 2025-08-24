#ifndef CGL_VAOBUFFERBUILDER_H
#define CGL_VAOBUFFERBUILDER_H

#include <cgl/core/buffer/vaobuffer.h>
#include <cgl/core/rendercontext.h>

namespace CGL {
class VAOBufferBuilder
{
public:
    static VAOBufferBuilder build();

    VAOBufferBuilder& setVertexData(const void* data, int size, RenderContext::DrawChangeMode mode);
    VAOBufferBuilder& setIndexData(const void* data, int size, RenderContext::DrawChangeMode mode);
    VAOBufferBuilder& setAttribute(int index, int components, int stride, int offset);
    VAOBuffer done();

private:
    VAOBufferBuilder();

private:
    VAOBuffer m_vao;
};
}

#endif // CGL_VAOBUFFERBUILDER_H
