#include <examples/lightscene.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>

CGL::LightScene::LightScene()
{
    m_shader = CGL::Shader("shaders/cube.vert", "shaders/cube.frag");
    m_lightShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");

    auto tex = TextureLoader::loadFromFile("textures/woodparquet/woodparquet_119_basecolor-1K.png");
    auto brick = TextureLoader::loadFromFile("textures/brick/brick.jpg");

    for (int i = -10; i < 10; i++) {
        for (int j = -10; j < 10; j++) {
            CGL::Node* node = new CGL::Node;
            node->addMesh(new CGL::Rectangle(tex));
            m_scene.append(node);
        }
    }

    m_lightCube = new CGL::Cube(brick);
}

void CGL::LightScene::use(CGL::Camera& camera, CGL::Transform model, CGL::Transform view, CGL::Transform projection)
{
    m_shader.use();

    static unsigned short count = 0;
    count += 10;
    static float xOffset = 0;
    static float yOffset = 0;

    xOffset += (count % 1 == 0 ? 0.1 : 0);
    yOffset += xOffset >= 6 ? 1: 0;
    xOffset = xOffset >= 6 ? -6: xOffset;
    yOffset = yOffset >= 6 ? -6 : yOffset;

    // glm::vec3 lightPos(xOffset, yOffset, 5);
    glm::vec3 lightPos(0, 0, 5);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_shader.setVec3("light.color", 1.0, 1.0, 1.0);
    m_shader.setVec3("light.position", lightPos);

    m_shader.setVec3("viewPos", camera.pos());
    m_shader.setInt("diffuseTex", 0);


    auto nodes = m_scene.nodes();
    int index = 0;

    for (int i = -10; i < 10; i++) {
        for (int j = -10; j < 10; j++) {
            CGL::Transform modif = model;
            modif.scale(10.0);
            modif.translateX(i);
            modif.translateY(j);
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

void CGL::LightScene::gammaOnOff()
{
    m_shader.use();
    auto currentState = m_shader.getBool("gammaEnabled");
    m_shader.setBool("gammaEnabled", !currentState);
}
