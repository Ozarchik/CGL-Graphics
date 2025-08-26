#ifndef CGL_DEFAULTPOSTPROCESSOR_H
#define CGL_DEFAULTPOSTPROCESSOR_H

#include <cgl/graphics/shader.h>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/graphics/postprocess/ipostprocesspass.h>
#include <memory>

namespace CGL {
class DefaultPostProcessor: public IPostProcessPass
{
public:
    DefaultPostProcessor();

    void apply(FrameBuffer& fbuffer) override;

private:
    std::shared_ptr<CGL::Shader> m_shader;
    std::shared_ptr<CGL::Mesh> m_quad;
};
}

#endif // CGL_DEFAULTPOSTPROCESSOR_H
