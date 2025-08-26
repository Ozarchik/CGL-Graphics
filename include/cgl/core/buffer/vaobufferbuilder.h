#ifndef CGL_VAOBUFFERBUILDER_H
#define CGL_VAOBUFFERBUILDER_H

#include <memory>
#include <cgl/core/buffer/vaobuffer.h>
#include <cgl/core/rendercontext.h>
#include <map>

namespace CGL {
class VAOBufferBuilder
{
public:
    static VAOBufferBuilder build();

    VAOBufferBuilder& setVertexData(const void* data, int size, RenderContext::DrawChangeMode mode);
    VAOBufferBuilder& setIndexData(const void* data, int size, RenderContext::DrawChangeMode mode);
    VAOBufferBuilder& setAttribute(int index, int components, int stride, int offset);
    std::shared_ptr<VAOBuffer> done();

private:
    VAOBufferBuilder();

private:
    struct Data {
        const void *data = nullptr;
        int size = 0;
        RenderContext::DrawChangeMode drawMode;

        bool isValid() {
            return data && size;
        }
    };

    struct Attribute {
        int index;
        int components;
        int stride;
        int offset;

        bool isValid() {
            return index > -1;
        }
    };

    // std::shared_ptr<VAOBuffer> m_vao;
    // const void *vertices;
    // int verticesSize;
    // RenderContext::DrawChangeMode vertDrawMode;

    // const void *indices;
    // int indicesSize;
    // RenderContext::DrawChangeMode indDrawMode;

    Data m_vertices;
    Data m_indices;
    std::map<int, Attribute> m_attributes;
};
}

#endif // CGL_VAOBUFFERBUILDER_H
