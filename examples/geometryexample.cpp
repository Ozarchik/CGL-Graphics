#include <examples/geometryexample.h>
#include <cgl/mesh/2D/rectangle.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/transform.h>

CGL::GeometryExample::GeometryExample()
{
    m_shader = CGL::Shader("shaders/geometry.vert", "shaders/geometry.frag", "shaders/geometry.geom");
    // m_scene.addMesh(new CGL::Rectangle);
    m_scene.addMesh(new CGL::Cube);
}

void CGL::GeometryExample::use(const Window &window, const Camera &camera)
{
    m_shader.use();
    CGL::Transform model, view, projection;
    model.scale(2.0f);
    model.translateX(-2.5f);
    model.translateZ(-10.0f);
    view = camera.getLookAt();
    projection.perspective(45.0f, window.aspect(), 1.0f, 500.0f);
    // projection.ortogonal(0, 800, 0, 600, 0.1f, 100.0f);

    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);

    CGL::Transform mvp = projection * view * model;

    static int16_t count = 0;
    mvp.translateX(count++/1000.0);
    m_shader.setMat4("MVP", mvp);

    m_shader.setFloat("time", count++/100.0);

    // glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(50.0f);

    for (const auto& m: m_scene.meshes()) {
        m->setPrimitiveType(GL_TRIANGLES);
        m->draw(m_shader);
    }
}
