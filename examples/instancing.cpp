#include "instancing.h"
#include "cube.h"

CGL::Instancing::Instancing()
{
    m_shader = CGL::Shader("shaders/instance.vert", "shaders/instance.frag");
    m_scene.addMesh(new CGL::Cube);


    int index = 0;
    float offset = 3.0f;

    m_shader.use();

    for (int i = -5; i < 5; i++) {
        for (int j = -5; j < 5; j++) {
            glm::vec2 translate;
            translate.x = (float)i * offset;
            translate.y = (float)j * offset;
            m_shader.setVec2(("offsets[" + std::to_string(index++) + "]"), translate);
        }
    }
}

void CGL::Instancing::use (
    const CGL::Transform& model,
    const CGL::Transform& view,
    const CGL::Transform& projection
) {
    m_shader.use();
    static int count = 0;
    count++;
    CGL::Transform modifModel = model;
    modifModel.translateZ(-50.0);
    modifModel.rotate(count/10.0f, 1.0, 1.0, 1.0);
    m_shader.setMat4("model", modifModel);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }

    modifModel.rotate(90.0, 1.0, 0.0, 0.0);
    m_shader.setMat4("model", modifModel);
    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }

    modifModel.rotate(90.0, 0.0, 1.0, 0.0);
    m_shader.setMat4("model", modifModel);
    for (const auto& m: m_scene.meshes()) {
        m->draw(m_shader);
    }
}
