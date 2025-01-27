#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "window.h"
#include "camera.h"

namespace CGL {
class InputController
{
public:
    InputController(CGL::Window* window, CGL::Camera* camera);

    void process();

private:
    static void mouseCallback(GLFWwindow* window, double x, double y);

private:
    GLFWwindow* m_window;
    inline static CGL::Camera* m_camera;
};
}

#endif // INPUTCONTROLLER_H
