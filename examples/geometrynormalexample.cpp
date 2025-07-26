#include <examples/geometrynormalexample.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/model/modelloader.h>

CGL::GeometryNormalExample::GeometryNormalExample()
{
    m_shader = CGL::Shader(
        "shaders/geometry.vert",
        "shaders/geometry.frag",
        "shaders/normalshow.geom"
    );

    m_scene.addMesh(new CGL::Sphere);
    // model.load("assets/sphere/model.obj");
    CGL::ModelLoader modelLoader;
    object = modelLoader.load("assets/backpack/backpack.obj");
    modelShader = CGL::Shader("shaders/model.vert", "shaders/model.frag");
}

void CGL::GeometryNormalExample::use(const Transform &model, const Transform &view, const Transform &projection)
{
    // CGL::Transform modif = worldTransform;
    // modif.translateX(10);
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);

    object.draw(m_shader);

    modelShader.use();
    modelShader.setMat4("model", model);
    modelShader.setMat4("view", view);
    modelShader.setMat4("projection", projection);

    object.draw(modelShader);

    // m_scene.render(m_shader);
}

