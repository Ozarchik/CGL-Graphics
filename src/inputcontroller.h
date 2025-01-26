#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "GLFW/glfw3.h"
#include "camera.h"
#include "window.h"

namespace CGL {
class InputController
{
public:
    InputController(CGL::Window *window, CGL::Camera* camera);

    void process();

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double x, double y);

private:
    GLFWwindow* m_window;
    inline static CGL::Camera* m_camera;
};
}

#endif // INPUTCONTROLLER_H
