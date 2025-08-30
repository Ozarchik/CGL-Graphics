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

float imgX = 0;
float imgY = 0;

float imgW = 0;
float imgH = 0;

// void CGL::MainWindow::renderScene()
// {
//     ImGui::Begin("3D scene (original + post)");

//     ImVec2 pos = ImGui::GetCursorScreenPos();           // верхний-левый экранный угол контента
//     ImVec2 avail = ImGui::GetContentRegionAvail();     // доступное пространство в окне

//     // Получаем реальные размеры фреймбуфера/текстуры (пиксели)
//     auto& fb = cglEngine().views().front().framebuffer;
//     int texW_px = 800;    // размер FBO в ПИКСЕЛЯХ
//     int texH_px = 800;

//     // Учитываем DPI / framebuffer scale -> ImGui использует логические координаты (points)
//     ImGuiIO& io = ImGui::GetIO();
//     float scaleX = io.DisplayFramebufferScale.x; // обычно 1.0 или 2.0 на ретина
//     float scaleY = io.DisplayFramebufferScale.y;

//     // Конвертируем размеры текстуры (пиксели) в координаты ImGui (points)
//     float texW = texW_px / scaleX;
//     float texH = texH_px / scaleY;

//     // dst — рисуем именно фиксированный размер (без масштабирования!)
//     // Центрируем текстуру в доступной области:
//     ImVec2 center  = ImVec2(pos.x + avail.x * 0.5f, pos.y + avail.y * 0.5f);
//     ImVec2 dstMin  = ImVec2(center.x - texW * 0.5f + imgX, center.y - texH * 0.5f + imgY);
//     ImVec2 dstMax  = ImVec2(dstMin.x + texW + imgW, dstMin.y + texH + imgH);

//     // Накладываем клип по содержимому окна — это автоматически обрежет края,
//     // когда окно меньше текстуры, причём обрезка будет симметричной вокруг центра.
//     ImGui::GetWindowDrawList()->PushClipRect(pos, ImVec2(pos.x + avail.x, pos.y + avail.y), true);

//     // Рисуем текстуру как есть (полные UV 0..1). Если ваша текстура требует flip по Y — используйте (0,1)-(1,0).
//     ImGui::GetWindowDrawList()->AddImage(
//         (ImTextureID)(intptr_t)fb->texture(), // или как у вас хранится ImTextureID
//         dstMin,
//         dstMax,
//         ImVec2(0, 1),
//         ImVec2(1, 0)
//         );

//     ImGui::GetWindowDrawList()->PopClipRect();

//     ImGui::End();
// }



void CGL::MainWindow::renderScene()
{
    ImGui::Begin("3D scene (original + post)", nullptr/*, ImGuiWindowFlags_NoMove*/);

    // static float splitX = cglCoreContext().width() / 2.0f;
    // float splitterThickness = 6.0f;

    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 size = ImGui::GetContentRegionAvail();

    glm::vec4 viewRect = cglCoreContext().viewport();

    int width   = viewRect.z;
    int height  = viewRect.w;
    int xoffset = (size.x - width)/2;
    int yoffset = (size.y - height)/2;

    // ImGui::GetWindowDrawList()->PushClipRect(
    //     ImVec2(pos.x + xoffset, pos.y + yoffset),
    //     ImVec2(pos.x + size.x, pos.y + size.y),
    //     true
    // );

    ImGui::GetWindowDrawList()->AddImage(
        cglEngine().views().front().framebuffer->texture(),
        ImVec2(pos.x + xoffset, pos.y + yoffset),
        ImVec2(pos.x + width + xoffset, pos.y + height + yoffset),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    // std::cout << "y: " << pos.y - std::abs(yoffset) << std::endl;
    // std::cout << "y offset: " << yoffset << std::endl;
    std::cout << std::endl;

    // std::cout << "pos: " << pos.x << ", " << pos.y << std::endl;
    // std::cout << "size: " << size.x << ", " << size.y << "\n" << std::endl;b


    // ImGui::GetWindowDrawList()->AddImage(
    //     cglEngine().views().front().postprocessor->targetTexture(),
    //     ImVec2(pos.x, pos.y),
    //     ImVec2(pos.x + size.x, pos.y + size.y),
    //     ImVec2(0, 1),
    //     ImVec2(1, 0)
    // );

    ImGui::GetWindowDrawList()->PopClipRect();

    // ImGui::SetCursorScreenPos(ImVec2(pos.x + splitX - splitterThickness * 0.5f, pos.y));
    // ImGui::InvisibleButton("splitter", ImVec2(splitterThickness, size.y));
    // if (ImGui::IsItemActive())
    //     splitX += ImGui::GetIO().MouseDelta.x;
    // if (ImGui::IsItemHovered())
    //     ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

    // ImU32 lineColor = IM_COL32(0, 0, 0, 255);
    // ImGui::GetWindowDrawList()->AddLine(
    //     ImVec2(pos.x + splitX, pos.y),
    //     ImVec2(pos.x + splitX, pos.y + size.y),
    //     lineColor,
    //     1.0f
    // );

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

    ImGui::Begin("Tools");
    // Viewport settings [begin]

    GLint v[4];
    glGetIntegerv(GL_VIEWPORT, v);

    if (ImGui::SliderInt("x", &v[0], 0.0, 800)) {
        glViewport(v[0], v[1], v[2], v[3]);
    }

    if (ImGui::SliderInt("y", &v[1], 0.0, 800)) {
        glViewport(v[0], v[1], v[2], v[3]);
    }

    if (ImGui::SliderInt("width", &v[2], 0.0, 800)) {
        glViewport(v[0], v[1], v[2], v[3]);
    }

    if (ImGui::SliderInt("height", &v[3], 0.0, 800)) {
        glViewport(v[0], v[1], v[2], v[3]);
    }

    if (ImGui::SliderFloat("xoffset", &imgX, -1000, 1000)) {

    }

    if (ImGui::SliderFloat("yoffset", &imgY, -1000, 1000)) {
    }

    static int cull = 0;
    if (ImGui::Button("cullface [front/back]")) {
        cglCoreContext().setCullFaceEnable(true);
        switch (cull++) {
            case 0: {
                cglCoreContext().setCullFaceMode(CoreContext::CullFaceMode::Front);
            } break;
            case 1: {
                cglCoreContext().setCullFaceMode(CoreContext::CullFaceMode::Back);
            } break;
            case 2: {
                cglCoreContext().setCullFaceMode(CoreContext::CullFaceMode::All);
            } break;
        }

        if (cull == 3) cull = 0;

        // if (front) {
        //     cglCoreContext().setCullFaceMode(CoreContext::CullFaceMode::Front);
        // } else {
        //     cglCoreContext().setCullFaceMode(CoreContext::CullFaceMode::Back);
        // }

        // std::cout << "front: " << front << std::endl;;
        // front = !front;
    }

    // Viewport settings [end]


    // renderNodeControlFrame();
    // renderCameraControlFrame();
    // renderSceneControlFrame();
    ImGui::End();

    UiManager::instance().render();
}
