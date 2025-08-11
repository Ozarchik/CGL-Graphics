#ifndef CGL_RENDERER_H
#define CGL_RENDERER_H

#include <cgl/grid.h>
#include <cgl/physics/raycast.h>
#include <cgl/camera.h>
#include <cgl/scene.h>
#include <cgl/framebuffer.h>

namespace CGL {
class Renderer
{
public:
    Renderer(CGL::Context& context);

    void render(CGL::Scene& scene, CGL::Camera& camera);
    CGL::FrameBuffer& framebuffer();

private:
    CGL::Context& m_context;
    CGL::FrameBuffer m_framebuffer;
    CGL::Shader m_framebufferShader;
    CGL::Grid grid;
};
}

#endif // CGL_RENDERER_H
