#ifndef CGL_FRAMEBUFFER_H
#define CGL_FRAMEBUFFER_H

#include <cgl/core/corecontext.h>

namespace CGL {
class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();

    void bind();
    void unbind();
    void detach();
    void rescale(int width, int height);
    unsigned int texture() const;

    void bindDefaultFramebuffer();
    void bindCustomFramebuffer();

private:
    unsigned int m_currentFramebuffer = 0;
    unsigned int m_fbo, m_rbo;
    unsigned int m_texture;
};
}

#endif // FRAMEBUFFER_H
