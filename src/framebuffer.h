#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "cube.h"

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

    void setStencil(GLenum mode, unsigned char mask = 0xff);
    void enableDepth(bool mode);

private:
    unsigned int fbo, rbo;
    unsigned int vao, vbo;
    unsigned int texture;

};
}

#endif // FRAMEBUFFER_H
