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

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    
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
    CGL::FrameBuffer framebuffer;

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

        // 1. We render 3D on framebuffer and then gets its as texture
        // 2. Pass texture to ImGui as image to render it on a ImGui window

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();    
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::NewFrame();

        // Main ImGui docking space
        // ImGuiWindowFlags imguiWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
        // ImGuiViewport* viewport = ImGui::GetMainViewport();
        // ImGui::SetNextWindowPos(viewport->Pos);
        // ImGui::SetNextWindowSize(viewport->Size);
        // ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        static bool init = true;
        ImGuiID dock_id_left, dock_id_right;
        if (init) {
            init = false;
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id);
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, &dock_id_left, &dock_id_right);
            ImGui::DockBuilderDockWindow("3D scene", dock_id_left);
            ImGui::DockBuilderDockWindow("Hello, CGL Graphics", dock_id_right);

            ImGui::DockBuilderFinish(dockspace_id);
        }


        // ImGui::Begin("MainDockSpace", nullptr, imguiWindowFlags);
        // ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
        // ImGui::DockSpace(dockspaceId, ImVec2(0.0, 0.0), ImGuiDockNodeFlags_None);
        // ImGui::End();



        ImGui::Begin("3D scene");

        float imguiWindowWidth = ImGui::GetContentRegionAvail().x;
        float imguiWindowHeight = ImGui::GetContentRegionAvail().y;

        // std::cout << "width: " << imguiWindowWidth << ", height: " << imguiWindowHeight << std::endl;

        framebuffer.rescale(imguiWindowWidth, imguiWindowHeight);
        glViewport(0, 0, imguiWindowWidth, imguiWindowHeight);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            framebuffer.texture(),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + imguiWindowWidth, pos.y + imguiWindowHeight),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

        ImGui::End();

        framebuffer.bind();

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

        framebuffer.unbind();
        
        // testFrame.update();

        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();

        ImGui::Begin("Hello, CGL Graphics", nullptr);
        ImGui::Text("Simple text");
        if (ImGui::Button("Apply")) {
        ImGui::Text("Button is clicked");
        }

        ImGui::End();

        // ImGui::Render();

        // m_editor.update();


        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();

        // TODO: Render the scene to a texture using an FBO
        //       and then display it in the window using ImGui::Image
        // GOAL: Split the window into left and right areas
        //       On the left, I'll render a settings panel,
        //       and on the right, I'll render the 3D scene

        /*  -----------------------
           |            |          |
           |            |          |
           |  Settings  |    3D    |
           |            |          |
           |            |          |
            -----------------------
        */

        m_window.update();

        // m_screenShader.use();
        // framebuffer.use();
        // m_screenShader.setInt("screen", 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        m_window.swapBuffers();
	}
}