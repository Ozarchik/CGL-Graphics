#include <cgl/application.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CGL::Application::initOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		std::abort();
	}

    glfwSetFramebufferSizeCallback(m_window.handler(), framebufferSizeCallback);

    glViewport(0, 0, m_window.width(), m_window.height());
}

CGL::Application::Application()
{
    CGL::Backtrace::init();
    m_window.init();
	initOpenGL();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window.handler(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    m_screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");
    m_meshShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    createTestObjects();
}

CGL::Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
    CGL::InputController inputController(&m_window, &m_camera);

    CGL::NormalMap normalMap(&m_window, &m_camera);
    CGL::FrameBuffer frameBuffer;

    float lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_FRAMEBUFFER_SRGB);

    CGL::FloorGenerator floorGen;
    CGL::Frame testFrame(&m_window);

    while (!glfwWindowShouldClose(m_window.handler())) {
        inputController.process();
        float currentFrame = glfwGetTime();

        float deltaTime = currentFrame - lastFrame;
        m_camera.correctSpeed(deltaTime);
        lastFrame = currentFrame;

        frameBuffer.bind();

        double timeVal = glfwGetTime() * 60;

        CGL::Transform model;
        CGL::Transform view = m_camera.getLookAt();
        CGL::Transform projection = CGL::Transform::makePerspective(45.0f, m_window.aspect(), 0.1f, 500.0f);

        floorGen.draw(m_camera, model, view, projection);

        m_meshShader.use();
        m_meshShader.setMVP(model, view, projection);
        m_meshShader.setMat4("view", view);
        m_meshShader.setVec3("light.color", 1.0, 1.0, 1.0);
        m_meshShader.setMat4("projection", projection);
        m_meshShader.setVec3("viewPos", m_camera.pos());
        m_meshShader.setInt("diffuseTex", 0);
        for (const auto& node: m_scene.nodes()) {
            node->update(m_meshShader);
        }

        frameBuffer.unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        testFrame.update();
        
        m_window.update();

        m_screenShader.use();
        m_screenShader.setInt("screen", 0);
        frameBuffer.use();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        m_window.swapBuffers();
	}
}