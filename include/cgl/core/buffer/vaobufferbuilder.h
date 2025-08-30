#ifndef CGL_VAOBUFFERBUILDER_H
#define CGL_VAOBUFFERBUILDER_H

#include <memory>
#include <cgl/core/buffer/vaobuffer.h>
#include <cgl/core/rendercontext.h>
#include <map>

namespace cgl {
class VAOBufferBuilder
{
public:
    static VAOBufferBuilder build();

    VAOBufferBuilder& setVertexData(const void* data, int size, cgl::DrawChangeMode mode);
    VAOBufferBuilder& setIndexData(const void* data, int size,  cgl::DrawChangeMode mode);
    VAOBufferBuilder& setAttribute(int index, int components, int stride, int offset);
    std::unique_ptr<VAOBuffer> done();

private:
    VAOBufferBuilder();

private:
    struct Data {
        const void *data = nullptr;
        int size = 0;
        cgl::DrawChangeMode drawMode;

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
    // cgl::DrawChangeMode vertDrawMode;

    // const void *indices;
    // int indicesSize;
    // cgl::DrawChangeMode indDrawMode;

    Data m_vertices;
    Data m_indices;
    std::map<int, Attribute> m_attributes;
};
}

#endif // CGL_VAOBUFFERBUILDER_H
