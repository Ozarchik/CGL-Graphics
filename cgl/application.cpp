#include <cgl/application.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/graphics/scene/node.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/graphics/model/modelloader.h>
#include <cgl/core/logger.h>
#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/material/materialbuilder.h>
#include <cgl/core/engine.h>

float screenVertices[] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

unsigned int quadVAO, quadVBO;

CGL::CoreContext& CGL::Application::m_context = CGL::CoreContext::instance();

CGL::Application::Application(/*int argc, char *argv[]*/)
    : m_camera(m_context)
    , m_commandDispatcher(m_scene)
    , m_inputController(&m_context, &m_camera)
    , m_renderer(m_context)
    , m_mainwindow(m_context, m_commandDispatcher, m_renderer)
    , m_raycast(m_context, m_scene, m_camera)
{
    CGL::Engine::instance().setActiveScene(&m_scene);
    CGL::Engine::instance().setActiveCamera(&m_camera);

    CGL_CheckErros();
    CGL::Backtrace::init();
    CGL::ResourceManager::init();

    m_meshShader = CGL::ResourceManager::loadDefaultShader();
    createTestObjects();

    // for screen

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    //
}

CGL::Application::~Application()
{

}

void CGL::Application::createTestObjects()
{
    CGL::Transform model;

    model.translateX(10.0f);
    std::shared_ptr<CGL::Node> node = std::make_shared<CGL::Node>(m_meshShader, model);
    node->addMesh(
        MeshBuilder
            ::build(MeshBuilder::Cube)
            .done(),
        MaterialBuilder
            ::build()
            .addTexture("terrazzo/terrazzo_17_normal-1K.png")
            .done()
    );
    m_scene.append(node);

    std::shared_ptr<CGL::Node> node2 = std::make_shared<CGL::Node>(m_meshShader, model.translateX(-3.0));
    node2->addMesh(
        MeshBuilder::build(MeshBuilder::Sphere)
            .done(),
        MaterialBuilder::build()
            .addTexture("planets/earth.bmp")
            .enabled(true)
            .done()
    );
    m_scene.append(node2);
    
    std::shared_ptr<CGL::Node> node3 = std::make_shared<CGL::Node>(m_meshShader, model.translateX(3.0));
    node3->addMesh(
        MeshBuilder
            ::build(MeshBuilder::Rectangle)
            .done(),
        MaterialBuilder
            ::build()
            .addTexture("brick/brick.jpg")
            .enabled(true)
            .done()
    );
    m_scene.append(node3);
    
    CGL::Transform scaleTransform;
    scaleTransform.scale(0.5);
}

CGL::Application &CGL::Application::instance()
{
    static Application app;
    return app;
}

void CGL::Application::run()
{
    m_inputController.addSubscriber(&m_raycast);

    while (m_context.isAlive()) {
        m_context.calcDeltaTime();
        draw();
	}
}

void CGL::Application::draw()
{
    CGL_CheckErros();

    m_context.update();

    m_commandDispatcher.process();
    m_camera.update();

    m_renderer.render(m_scene, m_camera);
    m_mainwindow.render();

    m_inputController.process();
    m_context.swapBuffers();
}
