#include <cgl/ui/mainwindow.h>
#include <imconfig.h>
#include <imgui.h>

#include <cgl/core/command/commanddispatcher.h>
#include <cgl/core/command/commands.h>
#include <cgl/managers/uimanager.h>
#include <glad/glad.h>
#include <cgl/core/engine.h>

CGL::MainWindow::MainWindow(CommandDispatcher& commandDispatcher, Renderer &renderer)
    : m_commandDispatcher(commandDispatcher), m_renderer(renderer)
{
    UiManager::instance().init();
    UiManager::instance().setDocking(true);
}

CGL::MainWindow::~MainWindow()
{
    UiManager::instance().deinit();
}

void CGL::MainWindow::init()
{
    UiManager::instance().newFrame();
}

void CGL::MainWindow::renderCameraControlFrame()
{
    ImGui::Begin("Camera control");

    Camera* camera = cglEngine().activeCamera();

    float fov = camera->fov();
    ImGui::SliderFloat("Fov", &fov, 0, 90.0f);

    camera->setFov(fov);

    ImGui::End();
}

void CGL::MainWindow::renderSceneControlFrame()
{
    ImGui::Begin("Scene control");

    // CGL::Scene* scene = cglEngine().activeScene();

    static int viewIndex = 0;
    if (ImGui::Button("View toggle")) {
        cglEngine().setActiveCamera(cglEngine().views()[viewIndex++].camera.get());
        viewIndex = viewIndex == 2 ? 0 : viewIndex;
    }

    ImGui::End();
}

void CGL::MainWindow::renderScene()
{
    ImGui::Begin("3D scene (original + post)");

    static float splitX = cglCoreContext().width() / 2.0f;
    float splitterThickness = 6.0f;

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::GetWindowDrawList()->AddImage(
        cglEngine().views().front().framebuffer->texture(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImGui::GetWindowDrawList()->PushClipRect(
        ImVec2(pos.x + splitX, pos.y),
        ImVec2(pos.x + size.x, pos.y + size.y),
        true
    );

    ImGui::GetWindowDrawList()->AddImage(
        cglEngine().views().front().postprocessor->targetTexture(),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImGui::GetWindowDrawList()->PopClipRect();

    ImGui::SetCursorScreenPos(ImVec2(pos.x + splitX - splitterThickness * 0.5f, pos.y));
    ImGui::InvisibleButton("splitter", ImVec2(splitterThickness, size.y));
    if (ImGui::IsItemActive())
        splitX += ImGui::GetIO().MouseDelta.x;
    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

    ImU32 lineColor = IM_COL32(0, 0, 0, 255);
    ImGui::GetWindowDrawList()->AddLine(
        ImVec2(pos.x + splitX, pos.y),
        ImVec2(pos.x + splitX, pos.y + size.y),
        lineColor,
        1.0f
    );

    ImGui::End();
}

void CGL::MainWindow::renderNodeControlFrame()
{
    ImGui::Begin("Node control");

    CGL::Scene* scene = cglEngine().activeScene();

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
    UiManager::instance().newFrame();

    renderScene();

    // ImGui::Begin("Tools");
    // renderNodeControlFrame();
    // renderCameraControlFrame();
    // renderSceneControlFrame();
    // ImGui::End();

    UiManager::instance().render();
}
