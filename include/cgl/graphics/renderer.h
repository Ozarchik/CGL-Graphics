#ifndef CGL_RENDERER_H
#define CGL_RENDERER_H

#include <cgl/graphics/grid.h>
#include <cgl/physics/raycast.h>
#include <cgl/core/camera.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/framebuffer.h>

namespace CGL {
class Renderer
{
public:
    Renderer(CGL::CoreContext& context);

    void render(CGL::Scene& scene, CGL::Camera& camera);
    CGL::FrameBuffer& framebuffer();

private:
    CGL::CoreContext& m_context;
    CGL::FrameBuffer m_framebuffer;
    CGL::Shader m_framebufferShader;
    CGL::Grid grid;
};
}

#endif // CGL_RENDERER_H
