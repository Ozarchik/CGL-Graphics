#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>

#include "window.h"
#include "camera.h"

namespace CGL {
class InputController
{
public:
    InputController(CGL::Window* window, CGL::Camera* camera);

    void process();

    bool isKeySpacePressed() const;
    void resetStates();

    void addSubscriber(CGL::Object* object);

private:
    static void keyNotify(const CGL::KeyType& keyType);
    static void mouseNotify(const CGL::MouseType &mouseType);
    static void mouseNotify(int dx, int dy);

    static void mouseCallback(GLFWwindow* window, double x, double y);

private:
    GLFWwindow* m_window;
    bool keySpacePressed = false;
    inline static std::vector<Object*> m_objects;
};
}

#endif // INPUTCONTROLLER_H
