#include <cgl/application.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/model/modelloader.h>
#include <cgl/logger.h>

CGL::Application::Application(int argc, char *argv[])
    : m_camera(m_context)
    , m_commandDispatcher(m_scene)
    , m_inputController(&m_context, &m_camera)
    , m_renderer(m_context)
    , m_mainwindow(m_context, m_commandDispatcher, m_renderer.framebuffer())
    , m_raycast(m_context, m_scene, m_camera)
{
    CGL_CheckErros();
    CGL::Backtrace::init();
    CGL::ResourceManager::init();

    m_meshShader = CGL::ResourceManager::loadDefaultShader();
    createTestObjects();
}

CGL::Application::~Application()
{

}

void CGL::Application::createTestObjects()
{
    CGL::Transform model;
    CGL::Node* node;
    CGL::Node* node2;
    CGL::Node* node3;

    model.translateX(10.0f);
    node = new CGL::Node(m_meshShader, model);
    node->addMesh(new CGL::Cube, CGL::Material({CGL::ResourceManager::loadTexture("terrazzo/terrazzo_17_normal-1K.png")}));
    // node = new CGL::Node(new Cube, m_meshShader, model);
    // m_scene.append(node);

    model.translateX(-3.0f);
    // node = new CGL::Node(new Sphere, m_meshShader, model);
    node2 = new CGL::Node(m_meshShader, model);
    node2->addMesh(new CGL::Sphere, CGL::Material({CGL::ResourceManager::loadTexture("planets/earth.bmp")}));
    // m_scene.append(node);
    
    model.translateX(6.0f);
    model.translateY(3.0f);
    node3 = new CGL::Node(m_meshShader, model);
    node3->addMesh(new CGL::Rectangle, CGL::Material({CGL::ResourceManager::loadTexture("brick/brick.jpg")}));
    node2->addChild(node);
    node3->addChild(node2);
    m_scene.append(node3);
    
    CGL::Transform scaleTransform;
    scaleTransform.scale(0.5);
    CGL::Node* modelNode1 = ResourceManager::loadModel("backpack2/backpack.obj");
    CGL::Node* modelNode2 = ResourceManager::loadModel("backpack2/backpack.obj");
    if (modelNode1 && modelNode2) {
        modelNode1->setTransform(scaleTransform);
        scaleTransform.translateY(10.0f);
        modelNode2->setTransform(scaleTransform);
        modelNode1->addChild(modelNode2);
        m_scene.append(modelNode1);
    }
}

void CGL::Application::loop()
{
    CGL::Grid grid;
    m_inputController.addSubscriber(&m_raycast);
    m_context.setWidth(800);
    m_context.setHeight(800);
    glViewport(0, 0, 800, 800);

    while (m_context.isAlive()) {
        CGL_CheckErros();
        m_inputController.process();
        m_commandDispatcher.process();
        m_camera.update();

        m_context.update();

        // m_mainwindow.init();
        // m_framebuffer.bind();

        CGL::Transform model;
        grid.draw(m_camera, model);
        model.translateY(8.0f);
        grid.draw(m_camera, model);
        m_raycast.draw();
        m_scene.render(m_camera);
        // m_framebuffer.unbind();
        // m_mainwindow.render();

        m_context.swapBuffers();
	}
}

void CGL::Application::draw()
{
    CGL_CheckErros();
    m_commandDispatcher.process();
    m_camera.update();

    m_context.update();

    m_mainwindow.init();

    m_renderer.render(m_scene, m_camera);
    m_mainwindow.render();

    m_inputController.process();
    m_context.swapBuffers();
}
