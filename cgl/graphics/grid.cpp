#include <cgl/graphics/grid.h>
#include <cgl/graphics/mesh/2D/rectangle.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/managers/resourcemanager.h>

CGL::Grid::Grid()
{
    m_shader = ResourceManager::loadShader("grid");
    m_lightShader = ResourceManager::loadDefaultShader();
    
    glm::vec3 greyLight = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 greyDark = glm::vec3(0.8, 0.8, 0.8);
    bool light = false;
    for (int i = 0; i < sideSize; i++) {
        for (int j = 0; j < sideSize; j++) {
            light = !light;

            std::shared_ptr<CGL::Node> node = std::make_shared<CGL::Node>(new CGL::Rectangle(greyLight), m_shader);
            m_scene.append(node);
        }
    }
}

void CGL::Grid::draw(CGL::Camera& camera, CGL::Transform model)
{
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", camera.getView());
    m_shader.setMat4("projection", camera.getProjection());
    m_shader.setVec3("viewPos", camera.pos());

    std::vector<std::shared_ptr<Node>> nodes = m_scene.nodes();
    int index = 0;

    float gradient = 0.0f;
    for (int i = 0; i < sideSize; i++) {
        for (int j = 0; j < sideSize; j++) {
            CGL::Transform modif = model;
            modif.scale(10.0);
            modif.rotate(90.0f, 1.0f, 0.0f, 0.0f);
            modif.translateX(i/*/8.0f*/);
            modif.translateY(j/*/8.0f*/);
            m_shader.use();
            // gradient += 0.005;
            // m_shader.setFloat("gradient", gradient);
            // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            // glPolygonOffset(1, 1);
            nodes[index]->setPrimitiveType(GL_TRIANGLES);
            // nodes[index]->setPrimitiveType(GL_LINE_LOOP);
            m_shader.setFloat("gradient", 0.2);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            nodes[index]->update(camera, modif);

            m_shader.use();
            m_shader.setFloat("gradient", 0.6);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            nodes[index]->update(camera, modif);
        }
    }
}
