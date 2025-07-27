#include <cgl/floorgenerator.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/texture/textureloader.h>

CGL::FloorGenerator::FloorGenerator()
{
    m_shader = CGL::Shader("shaders/floorgenerator.vert", "shaders/floorgenerator.frag");
    m_lightShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");

    auto tex = TextureLoader::loadFromFile("textures/woodparquet/woodparquet_119_basecolor-1K.png");
    auto brick = TextureLoader::loadFromFile("textures/brick/brick.jpg");
    
    for (int i = -sideSize; i < sideSize; i++) {
        for (int j = -sideSize; j < sideSize; j++) {
            CGL::Node* node = new CGL::Node;
            node->addMesh(new CGL::Rectangle(tex));
            m_scene.append(node);
        }
    }
    
    m_lightCube = new CGL::Cube(brick);
}

void CGL::FloorGenerator::draw(CGL::Camera& camera, CGL::Transform  model, CGL::Transform view, CGL::Transform projection)
{
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setVec3("light.color", 1.0, 1.0, 1.0);
    m_shader.setMat4("projection", projection);
    m_shader.setVec3("viewPos", camera.pos());
    m_shader.setInt("diffuseTex", 0);
    
    glm::vec3 lightPos(0, 0, 5);
    m_shader.setVec3("light.position", lightPos);

    glm::vec3 pos = camera.pos();
    int x = pos.x;
    int y = pos.y;

    /* * * * * *
    - - - - - -      -10  0 10   -20 -10 0       x - 10 x + 10
    *    c    *
    - - - - - -
    */

    auto nodes = m_scene.nodes();
    int index = 0;

    for (int i = -sideSize; i < sideSize; i++) {
        for (int j = -sideSize; j < sideSize; j++) {
            // glm::vec3 cellPos(x + i, y + j, 0);
            CGL::Transform modif = model;
            modif.scale(10.0);
            modif.rotate(90.0f, 1.0f, 0.0f, 0.0f);
            modif.translateX(i/8.0f); // Затем перемещаем с учётом масштаба
            modif.translateY(j/8.0f); // Используем Z для пола
            // modif.translateX(i);
            // modif.translateY(j);
            m_shader.setMat4("model", modif);
            nodes[index]->update(m_shader);
        }
    }

    model.reset();

    model.translate(lightPos);
    m_lightShader.use();
    m_lightShader.setMat4("model", model);
    m_lightShader.setMat4("view", view);
    m_lightShader.setMat4("projection", projection);
    m_lightCube->draw(m_lightShader);
}