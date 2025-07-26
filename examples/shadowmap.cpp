#include <examples/shadowmap.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>

CGL::ShadowMap::ShadowMap()
{
    m_shader = CGL::Shader("shaders/shadowmap.vert", "shaders/shadowmap.frag");

    for (int i = 0; i < 5; i++) {
        m_scene.addMesh(new CGL::Cube);
        m_scene.addMesh(new CGL::Sphere);
    }
}

void CGL::ShadowMap::use(const CGL::Window& window, const CGL::Camera& camera)
{
    m_shader.use();

    CGL::Transform projection;
    projection.perspective(45.0f, window.aspect(), 1.0f, 100.0f);
    m_shader.setMat4("view", camera.getLookAt());
    m_shader.setMat4("projection", projection);

    CGL::Transform model;
    for (int i = 0; i < m_scene.meshes().size(); i++) {
        model.reset();
        model.translateX(i*2.5);
        m_shader.setMat4("model", model);
        m_scene.meshes()[i]->draw(m_shader);
    }
}
