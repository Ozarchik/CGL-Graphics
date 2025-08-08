#include <cgl/ui/mainwindow.h>
#include <imconfig.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <cgl/logger.h>
#include <cgl/command/commanddispatcher.h>
#include <cgl/command/commands.h>

CGL::MainWindow::MainWindow(Context &context, Camera& camera, CommandDispatcher& commandDispatcher, FrameBuffer &framebuffer)
    : m_context(context), m_camera(camera), m_commandDispatcher(commandDispatcher), m_framebuffer(framebuffer)
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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();    
}

void CGL::MainWindow::update()
{
    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    static bool init = true;
    ImGuiID dock_id_left, dock_id_right;
    if (init) {
        init = false;
        auto wSize = ImGui::GetMainViewport()->Size;
        wSize.x *= 1.2;
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id);
        ImGui::DockBuilderSetNodeSize(dockspace_id, wSize);

        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);
        ImGui::DockBuilderDockWindow("3D scene", dock_id_left);
        ImGui::DockBuilderDockWindow("Hello, CGL Graphics", dock_id_right);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGui::Begin("3D scene");

    float imguiWindowWidth = m_context.width(); //ImGui::GetContentRegionAvail().x;
    float imguiWindowHeight = m_context.height(); //ImGui::GetContentRegionAvail().y;

    // m_framebuffer.rescale(imguiWindowWidth, imguiWindowHeight);
    glViewport(0, 0, m_context.width(), m_context.height());

    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += (ImGui::GetContentRegionAvail().x - imguiWindowWidth)/2.0f;
    pos.y += (ImGui::GetContentRegionAvail().y - imguiWindowHeight)/2.0f;
    ImGui::GetWindowDrawList()->AddImage(
        m_framebuffer.texture(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + imguiWindowWidth, pos.y + imguiWindowHeight),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();

    ImGui::Begin("Hello, CGL Graphics", nullptr);
    static bool init2 = false;
    if (ImGui::Button("Move")) {
        // if (init2)
        //     m_commandDispatcher.append(std::make_unique<CGL::MoveCommand>());
        // else
            // m_commandDispatcher.append(std::make_unique<CGL::CreateCubeCommand>());

        init2 = true;
    }

    static float x = 0.0f;
    static float y = 0.0f;
    static float z = 0.0f;

    if (ImGui::SliderFloat("Translate X", &x, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_unique<CGL::MoveCommand>(x, y, z));
    }

    if (ImGui::SliderFloat("Translate Y", &y, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_unique<CGL::MoveCommand>(x, y, z));
    }

    if (ImGui::SliderFloat("Translate Z", &z, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_unique<CGL::MoveCommand>(x, y, z));
    }
    ImGui::End();
}

void CGL::MainWindow::render()
{
    m_context.update();
    update();
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
