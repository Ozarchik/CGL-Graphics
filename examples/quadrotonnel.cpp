#include "quadrotonnel.h"
#include "cube.h"
#include "sphere.h"
#include "rectangle.h"
#include "textureloader.h"

CGL::QuadroTonel::QuadroTonel()
{
    m_shader = CGL::Shader("shaders/cube.vert", "shaders/cube.frag");
    auto texture = CGL::TextureLoader::loadFromFile("textures/planets/earth.bmp");

    for (int i = 0; i < 20; i++) {
        if (i % 3 == 0) {
            m_scene.addMesh(new CGL::Cube(texture));
        } else if (i % 3 == 1) {
            m_scene.addMesh(new CGL::Sphere(texture));
        } else {
            m_scene.addMesh(new CGL::Rectangle(texture));
        }
    }
}

void CGL::QuadroTonel::use(
    CGL::Transform& model,
    CGL::Transform& view,
    CGL::Transform& projection
)
{
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_shader.setBool("useColor", false);

    m_shader.setVec3("light.color", 1.0, 1.0, 1.0);
    m_shader.setVec3("light.position", 0.0, 0.0, 0.0);
    m_shader.setInt("diffuseTex", 0);

    // model.rotate(90, 0.0, 0.0, 0.0);
    for (int i = 0; i < m_scene.meshes().size(); i++) {
        model.translateX(2);
        m_shader.setMat4("model", model);
        m_scene.meshes()[i]->draw(m_shader);
    }
}
