#include <cgl/application.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/model/modelloader.h>



CGL::Application::Application(int argc, char *argv[])
    : m_camera(m_context)
    , m_inputController(&m_context, &m_camera)
    , m_mainwindow(m_context, m_framebuffer)
{
    CGL::Backtrace::init();

    m_meshShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    createTestObjects();
}

CGL::Application::~Application()
{

}

void CGL::Application::createTestObjects()
{
    auto brick = CGL::TextureLoader::loadFromFile("textures/brick/brick.jpg");
    CGL::Transform model;
    
    model.translateX(-3.0f);
    CGL::Node* node = new CGL::Node(new Sphere, m_meshShader, model);
    m_scene.append(node);
    
    model.translateX(3.0f);
    node = new CGL::Node(new Rectangle, m_meshShader, model);
    m_scene.append(node);
    
    model.translateX(6.0f);
    node = new CGL::Node(new Cube, m_meshShader, model);
    m_scene.append(node);

    ModelLoader loader;
    // m_scene.append(loader.load("assets/models/source/textures/carriage.fbx"));
    m_scene.append(loader.load("assets/models/backpack2/backpack.obj"));
}

void CGL::Application::loop()
{
    CGL::Grid grid;

    while (m_context.isAlive()) {
        m_inputController.process();

        m_camera.update();

        m_mainwindow.init();
        m_framebuffer.bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // m_framebuffer.enableDepth(true);


        CGL::Transform model;

        grid.draw(m_camera, model);

        model.translateY(10.0f);
        grid.draw(m_camera, model);

        m_scene.render(m_camera);
        m_framebuffer.unbind();

        m_mainwindow.update();
        m_context.update();

        m_mainwindow.render();

        m_context.swapBuffers();
	}
}
