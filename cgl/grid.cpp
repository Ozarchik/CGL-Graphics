#include <cgl/grid.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/texture/textureloader.h>
#include <cgl/resourcemanager.h>

CGL::Grid::Grid()
{
    m_shader = ResourceManager::loadShader("grid");
    m_lightShader = ResourceManager::loadDefaultShader();
    
    for (int i = -sideSize; i < sideSize; i++) {
        for (int j = -sideSize; j < sideSize; j++) {
            CGL::Node* node = new CGL::Node(new CGL::Rectangle, m_shader);
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

    auto nodes = m_scene.nodes();
    int index = 0;

    float gradient = 0.0f;
    for (int i = -sideSize; i < sideSize; i++) {
        for (int j = -sideSize; j < sideSize; j++) {
            CGL::Transform modif = model;
            modif.scale(10.0);
            modif.rotate(90.0f, 1.0f, 0.0f, 0.0f);
            modif.translateX(i/8.0f);
            modif.translateY(j/8.0f);
            m_shader.use();
            gradient += 0.005;
            m_shader.setFloat("gradient", gradient);
            nodes[index]->setPrimitiveType(GL_LINE_LOOP);
            nodes[index]->update(camera, modif);
        }
    }
}
