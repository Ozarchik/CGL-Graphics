#ifndef CGL_MAINWINDOW_H
#define CGL_MAINWINDOW_H

#include <cgl/core/corecontext.h>
#include <cgl/graphics/renderer.h>
#include <cgl/core/command/commanddispatcher.h>

#include <imgui.h>
#include <imgui_internal.h>


namespace cgl {
class MainWindow {
public:
    MainWindow(CommandDispatcher& commandDispatcher, cgl::Renderer& renderer);
    ~MainWindow();

    void init();
    void render();

private:
    void renderScene();
    void renderNodeControlFrame();
    void renderSceneControlFrame();
    void renderCameraControlFrame();

private:
    cgl::Renderer& m_renderer;
    cgl::CommandDispatcher& m_commandDispatcher;
};
}

#endif
