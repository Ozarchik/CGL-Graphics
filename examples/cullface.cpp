#include "cullface.h"
#include "cube.h"

CGL::CullFace::CullFace()
{
    m_shader = CGL::Shader("shaders/cullface.vert", "shaders/cullface.frag");
    m_scene.addMesh(new CGL::Cube);
}

void CGL::CullFace::use(const CGL::Window& window, const CGL::Camera& camera)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    CGL::Transform model, view, projection;
    view = camera.getLookAt();
    projection.perspective(45.0, window.aspect(), 1.0, 100);

    m_shader.use();
    m_shader.setMVP(model, view, projection);

    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }
}
