#ifndef CGL_APPLICATION_H
#define CGL_APPLICATION_H

#include <iostream>
#include <cmath>

#include <cgl/camera.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/texture/texture.h>
#include <cgl/transform.h>
#include <cgl/scene.h>
#include <cgl/shader.h>
#include <cgl/corecontext.h>
#include <cgl/inputcontroller.h>
#include <cgl/normalmap.h>
#include <cgl/framebuffer.h>
#include <cgl/vertexbuffer.h>
#include <cgl/grid.h>
#include <cgl/tools/backtrace/backtrace.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/resourcemanager.h>
#include <cgl/physics/raycast.h>
#include <cgl/renderer.h>

namespace CGL {
class Application
{
public:
    Application(/*int argc, char* argv[]*/);
    ~Application();
    void run();
    void draw();
    void createTestObjects();
    // void useScreenFramebuffer();

    static Application& instance();

private:
    static CGL::CoreContext& m_context;
    CGL::Scene m_scene;

    CGL::InputController m_inputController;

    CGL::Shader m_meshShader;
    CGL::Camera m_camera;

    CGL::MainWindow m_mainwindow;
    CGL::CommandDispatcher m_commandDispatcher;
    CGL::Raycast m_raycast;
    CGL::Renderer m_renderer;
};
}

#endif // APPLICATION_H
