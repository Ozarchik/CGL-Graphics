#ifndef CGL_FRAMEBUFFER_H
#define CGL_FRAMEBUFFER_H

#include <cgl/core/corecontext.h>

namespace CGL {
class FrameBuffer
{
public:
    FrameBuffer(CGL::CoreContext& context);
    ~FrameBuffer();

    void bind();
    void unbind();
    void detach();
    void rescale(int width, int height);
    unsigned int texture() const;

private:
    unsigned int m_fbo, m_rbo;
    unsigned int m_vao, m_vbo;
    unsigned int m_texture;

    CGL::CoreContext& m_context;
};
}

#endif // FRAMEBUFFER_H
