#include <cgl/grid.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/texture/textureloader.h>

CGL::Grid::Grid()
{

    m_shader = CGL::Shader("shaders/grid.vert", "shaders/grid.frag");
    m_lightShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");

    auto tex = TextureLoader::loadFromFile("textures/woodparquet/woodparquet_119_basecolor-1K.png");
    auto brick = TextureLoader::loadFromFile("textures/brick/brick.jpg");
    
    for (int i = -sideSize; i < sideSize; i++) {
        for (int j = -sideSize; j < sideSize; j++) {
            CGL::Node* node = new CGL::Node(new CGL::Rectangle(tex), m_shader);
            m_scene.append(node);
        }
    }
    
    // m_lightCube = new CGL::Cube(brick);
}

void CGL::Grid::draw(CGL::Camera& camera, CGL::Transform  model, CGL::Transform view, CGL::Transform projection)
{
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_shader.setVec3("viewPos", camera.pos());

    glm::vec3 pos = camera.pos();
    int x = pos.x;
    int y = pos.y;

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
            nodes[index]->setTransform(modif);
            m_shader.use();
            gradient += 0.005;
            m_shader.setFloat("gradient", gradient);
            nodes[index]->setPrimitiveType(GL_LINE_LOOP);
            nodes[index]->update();
        }
    }
}
