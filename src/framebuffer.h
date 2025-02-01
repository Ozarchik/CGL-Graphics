#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "cube.h"

namespace CGL {
class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void use();
    void bind();
    void unbind();
    void detach();

    void setStencil(GLenum mode, unsigned char mask = 0xff);
    void enableDepth(bool mode);

private:
    unsigned int fbo;
    unsigned int rbo;
    unsigned int texture;
    CGL::Cube* testCube;

    unsigned int quadVAO, quadVBO;
};
}

#endif // FRAMEBUFFER_H
