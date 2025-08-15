#ifndef CGL_MAINWINDOW_H
#define CGL_MAINWINDOW_H

#include <cgl/core/corecontext.h>
#include <cgl/graphics/renderer.h>
#include <cgl/core/command/commanddispatcher.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>

namespace CGL {
class MainWindow {
public:
    MainWindow(CGL::CoreContext& context, CommandDispatcher& commandDispatcher, CGL::Renderer& renderer);
    ~MainWindow();

    void init();
    void update();
    void render();

private:
    CGL::CoreContext& m_context;
    CGL::Renderer& m_renderer;
    CGL::CommandDispatcher& m_commandDispatcher;
};
}

#endif
