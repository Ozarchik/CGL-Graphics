#include <cgl/application.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

CGL::Application::Application(int argc, char *argv[])
    : m_camera(m_context)
{
    CGL::Backtrace::init();
    m_context.init();
	initOpenGL();    

    m_screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");
    m_meshShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    createTestObjects();
}

CGL::Application::~Application()
{

}

void CGL::Application::initOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        std::abort();
    }

    glfwSetFramebufferSizeCallback(m_context.handler(), framebufferSizeCallback);

    glViewport(0, 0, m_context.width(), m_context.height());
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
    CGL::InputController inputController(&m_context, &m_camera);

    CGL::FrameBuffer framebuffer;

    CGL::FloorGenerator floorGen;
    CGL::Frame testFrame(&m_context);
    CGL::MainWindow mainwindow(m_context, framebuffer);

    while (!glfwWindowShouldClose(m_context.handler())) {
        m_context.setWidth(viewportWidth);
        m_context.setHeight(viewportHeight);
        inputController.process();

        m_camera.update();

        
        mainwindow.init();

        framebuffer.bind();

        double timeVal = glfwGetTime() * 60;

        CGL::Transform model;
        CGL::Transform view = m_camera.getLookAt();
        CGL::Transform projection = CGL::Transform::makePerspective(45.0f, m_context.aspect(), 0.1f, 500.0f);

        floorGen.draw(m_camera, model, view, projection);

        m_meshShader.use();
        m_meshShader.setMVP(model, view, projection);
        m_meshShader.setVec3("light.color", 1.0, 1.0, 1.0);
        m_meshShader.setVec3("viewPos", m_camera.pos());

        m_scene.render(m_meshShader);

        framebuffer.unbind();

        mainwindow.update();
        m_context.update();

        mainwindow.render();
        
        m_context.swapBuffers();
	}
}
