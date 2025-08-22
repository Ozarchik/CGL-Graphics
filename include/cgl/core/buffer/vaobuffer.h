#ifndef CGL_VAOBUFFER_H
#define CGL_VAOBUFFER_H

namespace CGL {
class VAOBuffer
{
    friend class VAOBufferBuilder;

public:
    VAOBuffer();
    ~VAOBuffer();

    VAOBuffer(const VAOBuffer& other) = delete;
    VAOBuffer& operator=(const VAOBuffer& other) = delete;

    VAOBuffer(VAOBuffer&& other) noexcept;
    VAOBuffer& operator=(VAOBuffer&& other) noexcept;

    unsigned int id();

    void bind();
    void unbind();

    void reset();

    void enableAttribute(int index);
    void disableAttribute(int index);

// private:
    void setVertexData(const void *data, int size, bool staticDraw);
    void setIndexData(const void *data, int size, bool staticDraw);
    void setAttribute(int index, int components, int stride, int offset);

    void init();

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
};
}

#endif // CGL_VAOBUFFER_H
