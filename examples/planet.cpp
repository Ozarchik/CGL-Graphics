#include <examples/planet.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/model/modelloader.h>
#include <cgl/node.h>

constexpr unsigned int rockCount = 200;
glm::vec3 coords[rockCount];
glm::vec3 colors[rockCount];
float angles[rockCount];
float scales[rockCount];

float radius = 15.0;
float offset = 3.0f;

CGL::Planet::Planet()
{
    m_shaderInst.use();
    m_shaderInst = CGL::Shader(
        "shaders/instance.vert",
        "shaders/instance.frag"
    );

    m_shader.use();
    m_shader = CGL::Shader(
        "shaders/model.vert",
        "shaders/model.frag"
    );

    // m_scene.append(new CGL::Cube);
    CGL::Node* node = new CGL::Node;
    node->addMesh(new CGL::Sphere);
    m_scene.append(node);

    CGL::ModelLoader modelLoader;
    m_planet = modelLoader.load("assets/backpack/backpack.obj");
    // m_planet = modelLoader.load("assets/furniture-pack-3d-model/Sofa.obj");
    m_rock = modelLoader.load("assets/sphere/model.obj");

    for (int i = 0; i < rockCount; i++) {
        float angle = float(i)/rockCount * 360;
        float displacement;
        float x,y,z;

        displacement = (rand()/10 % (int) (2*offset*100)) / 100.0f - offset;
        x = sin(angle) * radius + displacement;

        displacement = (rand()/10 % (int) (2*offset*100)) / 100.0f - offset;
        y = 0.5 * displacement;

        displacement = (rand()/10 % (int) (2*offset*100)) / 100.0f - offset;
        z = cos(angle) * radius + displacement;

        float scale = (rand() % 100) / 1000.0f + 0.5f;
        float rotAngle = (rand() % 360);

        coords[i] = glm::vec3(x,y,z);
        colors[i] = glm::vec3(211/255.0f, 144/255.0f, 66/255.0f);
        // colors[i] = glm::vec3(rand()/(float)RAND_MAX*0.7, rand()/(float)RAND_MAX*0.5, rand()/(float)RAND_MAX * 0.5);
        scales[i] = scale;
        angles[i] = rotAngle;
    }
}

void CGL::Planet::use (
    const CGL::Transform& model,
    const CGL::Transform& view,
    const CGL::Transform& projection
)
{
    // -- [PLANET] --

    static long count = 0;
    const_cast<CGL::Transform&>(model).translateX(-5.0);
    const_cast<CGL::Transform&>(model).translateY(-0.0);
    const_cast<CGL::Transform&>(model).translateZ(-40.0);
    const_cast<CGL::Transform&>(model).rotate(45, 1.0, 0.0, 0.0);
    const_cast<CGL::Transform&>(model).rotate(count/5000.0f, 0.0, 1.0, 0.0);
    const_cast<CGL::Transform&>(model).scale(2.0);

    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_planet.draw(m_shader);
    const_cast<CGL::Transform&>(model).scale(0.5);


    // -- [ROCK] --

    for (int i = 0; i < rockCount; i++) {
        CGL::Transform modifModel = model;

        m_shaderInst.use();

        modifModel.translate(coords[i].x, coords[i].y, coords[i].z);
        modifModel.rotate(angles[i], 0.2f, 0.4f, 0.6f);
        modifModel.scale(scales[i]);
        modifModel.rotate(count++/1000.0f, 0.0, 1.0, 0.0);

        modifModel.scale(0.01);

        m_shaderInst.setMat4("model", modifModel);
        m_shaderInst.setMat4("view", view);
        m_shaderInst.setMat4("projection", projection);
        // m_shaderInst.setVec3("rockColor", colors[i]);

        m_rock.draw(m_shaderInst);
    }

    count++;
}
