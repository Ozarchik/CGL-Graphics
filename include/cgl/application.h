#ifndef CGL_APPLICATION_H
#define CGL_APPLICATION_H


#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <cmath>

#include <cgl/camera.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/texture/texture.h>
#include <cgl/transform.h>
#include <cgl/model/model.h>
#include <cgl/scene.h>
#include <cgl/shader.h>
#include <cgl/window.h>
#include <cgl/inputcontroller.h>
#include <cgl/normalmap.h>
#include <cgl/framebuffer.h>
#include <cgl/vertexbuffer.h>
#include <cgl/floorgenerator.h>
#include <cgl/ui/frame.h>
#include <cgl/tools/backtrace/backtrace.h>


namespace CGL {
class Application
{
public:
    Application();
    ~Application();
    void loop();
    void initOpenGL();
    void createTestObjects();

private:
    CGL::Window m_window;
    CGL::Camera m_camera;
    CGL::Shader m_screenShader;
    CGL::Shader m_meshShader;
    CGL::Scene m_scene;
};
}

#endif // APPLICATION_H
