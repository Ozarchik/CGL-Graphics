#ifndef CGL_MAINWINDOW_H
#define CGL_MAINWINDOW_H

#include <cgl/corecontext.h>
#include <cgl/renderer.h>
#include <cgl/command/commanddispatcher.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace CGL {
class MainWindow {
public:
    MainWindow(CGL::CoreContext& context, CommandDispatcher& commandDispatcher, CGL::FrameBuffer& framebuffer);
    ~MainWindow();

    void init();
    void update();
    void render();

private:
    CGL::CoreContext& m_context;
    CGL::FrameBuffer& m_framebuffer;
    CGL::CommandDispatcher& m_commandDispatcher;
};
}

#endif
