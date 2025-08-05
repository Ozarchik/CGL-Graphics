#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <vector>

#include <cgl/context.h>
#include <cgl/camera.h>
#include <cgl/event/event.h>

namespace CGL {
class InputController
{
public:
    InputController(CGL::Context* window, CGL::Camera* camera);

    void process();

    bool isKeySpacePressed() const;

    void addSubscriber(CGL::Object* object);

private:
    static void keyNotify(const CGL::KeyType& keyType);
    static void mouseNotify(const CGL::MouseType &mouseType);
    static void mouseNotify(int dx, int dy);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modes);
    static void mouseCallback(GLFWwindow* window, double x, double y);

private:
    inline static GLFWwindow* winHandler;
    CGL::Context* m_context;
    bool keySpacePressed = false;
    inline static std::vector<Object*> m_objects;
};
}

#endif // INPUTCONTROLLER_H
