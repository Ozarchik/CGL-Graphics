#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// #include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/cube.h>

namespace CGL {
class FrameBuffer
{
public:
    FrameBuffer(int width = 800, int height = 600);
    ~FrameBuffer();

    void use();
    void bind();
    void unbind();
    void detach();
    void rescale(int width, int height);
    unsigned int texture() const;

    void setStencilMode(GLenum mode, unsigned char mask = 0xff);
    void setDepthMode(bool mode);

private:
    unsigned int m_fbo, m_rbo;
    unsigned int m_vao, m_vbo;
    unsigned int m_texture;

};
}

#endif // FRAMEBUFFER_H
