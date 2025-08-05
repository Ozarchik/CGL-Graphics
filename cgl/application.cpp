#include <cgl/application.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>
#include <cgl/ui/mainwindow.h>



CGL::Application::Application(int argc, char *argv[])
    : m_camera(m_context)
    , m_inputController(&m_context, &m_camera)
    , m_mainwindow(m_context, m_framebuffer)
{
    CGL::Backtrace::init();

    m_screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");
    m_meshShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    createTestObjects();
}

CGL::Application::~Application()
{

}


void CGL::Application::createTestObjects()
{
    auto brick = CGL::TextureLoader::loadFromFile("textures/brick/brick.jpg");
    // m_scene.append(new Cube(brick));
    CGL::Node* node = new CGL::Node;
    node->addMesh(new Sphere(brick));
    node->addMesh(new Rectangle(brick));

    m_scene.append(node);
}

void CGL::Application::loop()
{
    CGL::Grid grid;

    while (m_context.isAlive()) {
        m_inputController.process();

        m_camera.update();

        m_mainwindow.init();
        // m_context.update();

        m_framebuffer.bind();

        CGL::Transform model;
        CGL::Transform view = m_camera.getLookAt();
        CGL::Transform projection = CGL::Transform::makePerspective(45.0f, m_context.aspect(), 0.1f, 500.0f);

        grid.draw(m_camera, model, view, projection);

        m_meshShader.use();
        m_meshShader.setMVP(model, view, projection);
        m_meshShader.setVec3("light.color", 1.0, 1.0, 1.0);
        m_meshShader.setVec3("viewPos", m_camera.pos());

        m_scene.render(m_meshShader);

        m_framebuffer.unbind();

        m_mainwindow.update();
        m_context.update();

        m_mainwindow.render();
        
        m_context.swapBuffers();
	}
}
