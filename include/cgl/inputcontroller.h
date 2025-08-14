#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>

#include <cgl/corecontext.h>
#include <cgl/camera.h>
#include <cgl/event/event.h>

namespace CGL {
class InputController
{
public:
    InputController(CGL::CoreContext* window, CGL::Camera* camera);

    void process();
    bool isKeySpacePressed() const;
    void addSubscriber(CGL::Object* object);

private:
    static void keyNotify(KeyType type, KeyAction action, KeyModifier modifier);
    static void mouseNotify(int dx, int dy, MouseState state = {});
    static void wheelNotify(double dx, double dy, MouseWheelState state = {});

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modes);
    static void scrollCallback(GLFWwindow* window, double dx, double dy);
    static void mouseCallback(GLFWwindow* window, double x, double y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
    inline static GLFWwindow* winHandler;
    CGL::CoreContext* m_context;
    bool keySpacePressed = false;
    inline static std::vector<CGL::Object*> m_objects;
    inline static double m_mouseX, m_mouseY;
};
}

#endif // INPUTCONTROLLER_H
