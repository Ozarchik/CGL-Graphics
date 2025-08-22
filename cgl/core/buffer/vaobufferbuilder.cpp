#include <cgl/core/buffer/vaobufferbuilder.h>
#include <cgl/utility/logger.h>
#include <utility>

CGL::VAOBufferBuilder CGL::VAOBufferBuilder::build()
{
    
    return VAOBufferBuilder();
}

CGL::VAOBufferBuilder::VAOBufferBuilder()
{
    m_vao.init();
    m_vao.bind();
}

CGL::VAOBuffer CGL::VAOBufferBuilder::done()
{
    m_vao.unbind();
    return std::move(m_vao);
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setVertexData(const void *data, int size, bool staticDraw)
{
    m_vao.setVertexData(data, size, staticDraw);
    return *this;
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setIndexData(const void* data, int size, bool staticDraw)
{
    m_vao.setIndexData(data, size, staticDraw);
    return *this;
}

CGL::VAOBufferBuilder& CGL::VAOBufferBuilder::setAttribute(int index, int components, int stride, int offset)
{
    m_vao.setAttribute(index, components, stride, offset);
    return *this;
}
