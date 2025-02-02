#ifndef STENCIL_H
#define STENCIL_H

#include "shader.h"
#include "scene.h"
#include "window.h"
#include "camera.h"
#include "framebuffer.h"

namespace CGL {
class Stencil
{
public:
    Stencil();
    void use(const CGL::Window &window, const CGL::Camera &camera);

private:
    CGL::Shader m_shader;
    CGL::Scene m_scene;
    CGL::FrameBuffer m_frameBuffer;
};
}

#endif // STENCIL_H
