#include <examples/quadrotonnel.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>

CGL::QuadroTonel::QuadroTonel()
{
    m_shader = CGL::Shader("shaders/cube.vert", "shaders/cube.frag");
    auto texture = CGL::TextureLoader::loadFromFile("textures/planets/earth.bmp");

    // for (int i = 0; i < 20; i++) {
    //     if (i % 3 == 0) {
    //         m_scene.append(new CGL::Cube(texture));
    //     } else if (i % 3 == 1) {
    //         m_scene.append(new CGL::Sphere(texture));
    //     } else {
    //         m_scene.append(new CGL::Rectangle(texture));
    //     }
    // }

    CGL::Node* node = new CGL::Node;
    node->addMesh(new CGL::Sphere(texture));
    m_scene.append(node);
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

    model.translateZ(5);
    model.rotate(-90, 1.0, 0.0, 0.0);
    for (int i = 0; i < m_scene.nodes().size(); i++) {
        // model.translateX(2);
        m_shader.setMat4("model", model);
        m_scene.nodes()[i]->update(m_shader);
    }
}
