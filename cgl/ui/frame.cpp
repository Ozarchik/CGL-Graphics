#include <cgl/ui/frame.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


CGL::Frame::Frame(CGL::Window* window)
    : m_window(window)
{
    
}

void CGL::Frame::update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello, CGL Graphics");
    ImGui::Text("Simple text");
    if (ImGui::Button("Apply")) {
        ImGui::Text("Button is clicked");
    }

    ImGui::End();

    ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

