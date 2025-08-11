#include <cgl/renderer.h>

CGL::Renderer::Renderer(CGL::Context &context)
    : m_context(context)
    , m_framebuffer(context.width(), context.height())
{}

void CGL::Renderer::render(Scene &scene, Camera &camera)
{
    m_framebuffer.bind();
    CGL::Transform model;
    model.translateY(-15.0f);
    grid.draw(camera, model);
    model.translateY(30.0f);
    grid.draw(camera, model);
    scene.render(camera);
    scene.render(camera);
    m_framebuffer.unbind();
}

CGL::FrameBuffer &CGL::Renderer::framebuffer()
{
    return m_framebuffer;
}
