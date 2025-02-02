#include "stencil.h"
#include "cube.h"

CGL::Stencil::Stencil()
{
    m_shader = CGL::Shader("shaders/stencil.vert", "shaders/stencil.frag");
    m_scene.addMesh(new CGL::Cube);
}

void CGL::Stencil::use(const CGL::Window& window, const CGL::Camera& camera)
{
    m_frameBuffer.setStencil(GL_ALWAYS, 0xff);

    m_shader.use();
    CGL::Transform model, view, projection;
    view = camera.getLookAt();
    projection.perspective(45.0f, window.aspect(), 1.0f, 100.0f);
    CGL::Transform mvp = projection * view * model;
    m_shader.use();
    m_shader.setMat4("MVP", mvp);

    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }

    m_frameBuffer.setStencil(GL_NOTEQUAL, 0x00);
    m_frameBuffer.enableDepth(false);

    model.translateX(5.0f);
    mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);
    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }

    m_frameBuffer.setStencil(GL_ALWAYS);
    m_frameBuffer.enableDepth(true);
}
