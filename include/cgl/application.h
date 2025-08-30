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
#include <cgl/graphics/animationsystem.h>

namespace cgl {
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
    cgl::Scene m_scene;

    cgl::InputController m_inputController;

    cgl::MainWindow m_mainwindow;
    cgl::CommandDispatcher m_commandDispatcher;
    cgl::Raycast m_raycast;
    cgl::Renderer m_renderer;
    cgl::AnimationSystem m_animation;
};
}

#endif // APPLICATION_H
