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
    , m_mainwindow(m_context, m_commandDispatcher, m_framebuffer)
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

    model.translateX(10.0f);
    node = new CGL::Node(m_meshShader, model);
    node->addMesh(new CGL::Cube, CGL::Material({CGL::ResourceManager::loadTexture("terrazzo/terrazzo_17_normal-1K.png")}));
    // node = new CGL::Node(new Cube, m_meshShader, model);
    m_scene.append(node);

    model.translateX(-3.0f);
    // node = new CGL::Node(new Sphere, m_meshShader, model);
    node = new CGL::Node(m_meshShader, model);
    node->addMesh(new CGL::Sphere, CGL::Material({CGL::ResourceManager::loadTexture("planets/earth.bmp")}));
    m_scene.append(node);
    
    model.translateX(6.0f);
    model.translateY(3.0f);
    node = new CGL::Node(m_meshShader, model);
    node->addMesh(new CGL::Rectangle, CGL::Material({CGL::ResourceManager::loadTexture("brick/brick.jpg")}));
    m_scene.append(node);
    
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

    while (m_context.isAlive()) {
        CGL_CheckErros();
        m_inputController.process();
        m_commandDispatcher.process();

        m_camera.update();

        m_mainwindow.init();
        m_framebuffer.bind();

        CGL::Transform model;
        grid.draw(m_camera, model);
        model.translateY(8.0f);
        grid.draw(m_camera, model);

        m_scene.render(m_camera);
        m_framebuffer.unbind();
        m_mainwindow.render();

        m_context.swapBuffers();
	}
}
