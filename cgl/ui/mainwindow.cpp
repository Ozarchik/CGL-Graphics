#include <cgl/ui/mainwindow.h>
#include <imconfig.h>
#include <imgui.h>

#include <cgl/core/logger.h>
#include <cgl/core/command/commanddispatcher.h>
#include <cgl/core/command/commands.h>
#include <cgl/managers/uimanager.h>
#include <glad/glad.h>
#include <cgl/core/engine.h>

CGL::MainWindow::MainWindow(CoreContext &context, CommandDispatcher& commandDispatcher, Renderer &renderer)
    : m_context(context), m_commandDispatcher(commandDispatcher), m_renderer(renderer)
{
    CGL::UiManager::instance().init();
}

CGL::MainWindow::~MainWindow()
{
    CGL::UiManager::instance().deinit();
}

void CGL::MainWindow::init()
{
    CGL::UiManager::instance().newFrame();
}

void CGL::MainWindow::renderCameraControlFrame()
{
    ImGui::Begin("Camera control");

    CGL::Camera* camera = CGL::Engine::instance().activeCamera();

    float fov = camera->fov();
    ImGui::SliderFloat("Fov", &fov, 0, 90.0f);

    camera->setFov(fov);

    ImGui::End();
}

void CGL::MainWindow::renderSceneControlFrame()
{
    ImGui::Begin("Scene control");

    CGL::Scene* scene = CGL::Engine::instance().activeScene();

    ImGui::End();
}

void CGL::MainWindow::renderScene()
{
    ImGui::Begin("3D scene");

    float imguiWindowWidth = m_context.width();
    float imguiWindowHeight = m_context.height();

    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += (ImGui::GetContentRegionAvail().x - imguiWindowWidth)/2.0f;
    pos.y += (ImGui::GetContentRegionAvail().y - imguiWindowHeight)/2.0f;
    ImGui::GetWindowDrawList()->AddImage(
        m_renderer.framebuffer().texture(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + imguiWindowWidth, pos.y + imguiWindowHeight),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();
}

void CGL::MainWindow::renderNodeControlFrame()
{
    ImGui::Begin("Node control", nullptr);

    CGL::Scene* scene = CGL::Engine::instance().activeScene();

    float x = 0;
    float y = 0;
    float z = 0;

    std::optional node = scene->selectedNode();
    if (node.has_value()) {
        auto pos = node.value()->transform().data()[3]; // last col in mat4
        x = pos.x;
        y = pos.y;
        z = pos.z;
    }

    if (ImGui::SliderFloat("Translate X", &x, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_shared<CGL::MoveCommand>(x, y, z));
    }

    if (ImGui::SliderFloat("Translate Y", &y, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_shared<CGL::MoveCommand>(x, y, z));
    }

    if (ImGui::SliderFloat("Translate Z", &z, -10.0f, 10.0f)) {
        m_commandDispatcher.append(std::make_shared<CGL::MoveCommand>(x, y, z));
    }

    ImGui::End();
}

void CGL::MainWindow::render()
{
    CGL::UiManager::instance().newFrame();

    // CGL::CoreContext::instance().update();

    UiManager::instance().enableDocking();

    renderScene();
    renderNodeControlFrame();
    renderCameraControlFrame();
    renderSceneControlFrame();

    CGL::UiManager::instance().render();
}
