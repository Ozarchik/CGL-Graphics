#ifndef CGL_MAINWINDOW_H
#define CGL_MAINWINDOW_H

#include <cgl/context.h>
#include <cgl/framebuffer.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace CGL {
class MainWindow {
public:
    MainWindow(CGL::Context& context, CGL::FrameBuffer& framebuffer);
    ~MainWindow();

    void init();
    void update();
    void render();

private:
    CGL::Context& m_context;
    CGL::FrameBuffer& m_framebuffer;
};
}

#endif
