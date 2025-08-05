#include <cgl/ui/mainwindow.h>
#include <imconfig.h>
#include <imgui.h>
#include <imgui_internal.h>

CGL::MainWindow::MainWindow(Context &context, FrameBuffer &framebuffer)
    : m_context(context), m_framebuffer(framebuffer)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_context.handler(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

CGL::MainWindow::~MainWindow() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void CGL::MainWindow::init()
{
    // 1. We render 3D on framebuffer and then gets its as texture
    // 2. Pass texture to ImGui as image to render it on a ImGui window

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();    
}

void CGL::MainWindow::update()
{
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

        m_framebuffer.rescale(imguiWindowWidth, imguiWindowHeight);
        glViewport(0, 0, m_context.width(), m_context.height());

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            m_framebuffer.texture(),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + imguiWindowWidth, pos.y + imguiWindowHeight),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

        ImGui::End();

        ImGui::Begin("Hello, CGL Graphics", nullptr);
        ImGui::Text("Simple text");
        if (ImGui::Button("Apply")) {
        ImGui::Text("Button is clicked");
        }

        ImGui::End();
}

void CGL::MainWindow::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
