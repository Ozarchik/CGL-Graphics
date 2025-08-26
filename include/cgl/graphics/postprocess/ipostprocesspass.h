#ifndef CGL_IPOSTPROCESSPASS_H
#define CGL_IPOSTPROCESSPASS_H

#include <cgl/core/rendercontext.h>
#include <cgl/graphics/framebuffer.h>

namespace CGL {

class IPostProcessPass {
public:
    IPostProcessPass() = default;
    virtual ~IPostProcessPass() = default;
    virtual void apply(FrameBuffer& input) = 0;
    uint32_t targetTexture() const;

protected:
    FrameBuffer m_targetFrambuffer;
};
}

#endif // CGL_IPOSTPROCESSPASS_H
