#include <cgl/core/buffer/vaobufferbuilder.h>
#include <utility>

CGL::VAOBufferBuilder CGL::VAOBufferBuilder::build()
{
    return VAOBufferBuilder();
}

CGL::VAOBufferBuilder::VAOBufferBuilder()
{
    // m_vao->init();
    // m_vao->bind();
}

std::unique_ptr<CGL::VAOBuffer> CGL::VAOBufferBuilder::done()
{
    // m_vao->unbind();
    std::unique_ptr<VAOBuffer> buffer = std::make_unique<VAOBuffer>();
    buffer->init();
    buffer->bind();

    if (m_vertices.isValid())
        buffer->setVertexData(m_vertices.data, m_vertices.size, m_vertices.drawMode);
    if (m_indices.isValid())
        buffer->setIndexData(m_indices.data, m_indices.size, m_indices.drawMode);

    for (auto& atr: m_attributes) {
        if (atr.second.isValid())
            buffer->setAttribute(atr.second.index, atr.second.components, atr.second.stride, atr.second.offset);
    }

    buffer->unbind();
    return buffer;
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setVertexData(const void *data, int size, RenderContext::DrawChangeMode mode)
{
    // m_vao->setVertexData(data, size, mode);
    if (data && size) {
        m_vertices = Data {
            .data = data,
            .size = size,
            .drawMode = mode
        };
    }

    return *this;
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setIndexData(const void* data, int size, RenderContext::DrawChangeMode mode)
{
    // m_vao->setIndexData(data, size, mode);
    if (data && size) {
        m_indices = Data {
            .data = data,
            .size = size,
            .drawMode = mode
        };
    }

    return *this;
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setAttribute(int index, int components, int stride, int offset)
{
    // m_vao->setAttribute(index, components, stride, offset);
    m_attributes[index] = {
        .index = index,
        .components = components,
        .stride = stride,
        .offset = offset,
    };
    return *this;
}
