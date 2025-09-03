#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>

#include <cgl/core/corecontext.h>
#include <cgl/core/camera.h>
#include <cgl/core/event/event.h>

namespace cgl {
class InputController
{
public:
    InputController();

public:
    void process();
    bool isKeySpacePressed() const;
    void addSubscriber(cgl::Object* object);

    static InputController& instance();

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
    bool keySpacePressed = false;
    inline static std::vector<cgl::Object*> m_objects;
    inline static double m_mouseX, m_mouseY;
};

InputController& cglInputController();

}

#endif // INPUTCONTROLLER_H
