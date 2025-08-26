#include <cgl/graphics/postprocess/ipostprocesspass.h>

uint32_t CGL::IPostProcessPass::targetTexture() const
{
    return m_targetFrambuffer.texture();
}
