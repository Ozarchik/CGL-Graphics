#ifndef CGL_APPLICATION_H
#define CGL_APPLICATION_H

#include <cmath>

#include <cgl/core/camera.h>
#include <cgl/graphics/mesh/3D/cube.h>
#include <cgl/graphics/mesh/3D/sphere.h>
#include <cgl/graphics/texture/texture.h>
#include <cgl/core/transform.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/shader.h>
#include <cgl/core/corecontext.h>
#include <cgl/core/event/inputcontroller.h>
#include <cgl/graphics/normalmap.h>
#include <cgl/graphics/framebuffer.h>
#include <cgl/graphics/vertex/vertexbuffer.h>
#include <cgl/graphics/grid.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/managers/resourcemanager.h>
#include <cgl/physics/raycast.h>
#include <cgl/graphics/renderer.h>

namespace CGL {
class Application
{
public:
    Application(/*int argc, char* argv[]*/);
    ~Application();
    void run();
    void draw();
    void createTestObjects();
    void createTerrainExample();

    static Application& instance();

private:
    CGL::Scene m_scene;

    CGL::InputController m_inputController;

    CGL::MainWindow m_mainwindow;
    CGL::CommandDispatcher m_commandDispatcher;
    CGL::Raycast m_raycast;
    CGL::Renderer m_renderer;
};
}

#endif // APPLICATION_H
