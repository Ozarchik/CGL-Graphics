#include <cgl/graphics/grid.h>
#include <cgl/graphics/mesh/2D/rectangle.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/managers/resourcemanager.h>

cgl::Grid::Grid()
{
    glm::vec3 greyLight = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 greyDark = glm::vec3(0.8, 0.8, 0.8);
    bool light = false;
    for (int i = 0; i < sideSize; i++) {
        for (int j = 0; j < sideSize; j++) {
            light = !light;
            std::shared_ptr<cgl::Node> node = std::make_shared<cgl::Node>(
                std::make_shared<cgl::Rectangle>(greyLight),
                ResourceManager::loadShader("grid")
            );
            m_scene.append(node);
        }
    }
}

void cgl::Grid::draw(cgl::Camera& camera, cgl::Transform model)
{
    std::vector<std::shared_ptr<Node>> nodes = m_scene.nodes();
    int index = 0;

    float gradient = 0.0f;
    for (int i = 0; i < sideSize; i++) {
        for (int j = 0; j < sideSize; j++) {
            cgl::Transform modif = model;
            modif.scale(10.0);
            modif.rotate(90.0f, 1.0f, 0.0f, 0.0f);
            modif.translateX(i/*/8.0f*/);
            modif.translateY(j/*/8.0f*/);
            nodes[index]->setPrimitiveType(cgl::RenderContext::Primitive::Triangle);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            nodes[index]->update(camera, modif);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            nodes[index]->update(camera, modif);
        }
    }
}
