#ifndef CGL_APPLICATION_H
#define CGL_APPLICATION_H



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
#include <cgl/context.h>
#include <cgl/inputcontroller.h>
#include <cgl/normalmap.h>
#include <cgl/framebuffer.h>
#include <cgl/vertexbuffer.h>
#include <cgl/grid.h>
#include <cgl/ui/frame.h>
#include <cgl/ui/editor.h>
#include <cgl/tools/backtrace/backtrace.h>
#include <cgl/ui/mainwindow.h>


namespace CGL {
class Application
{
public:
    Application(int argc, char* argv[]);
    ~Application();
    void loop();
    void createTestObjects();

private:
    CGL::Context m_context;
    CGL::Scene m_scene;

    CGL::InputController m_inputController;
    CGL::FrameBuffer m_framebuffer;
    CGL::MainWindow m_mainwindow;

    CGL::Camera m_camera;
    CGL::Shader m_meshShader;
    CGL::Editor m_editor;
};
}

#endif // APPLICATION_H
