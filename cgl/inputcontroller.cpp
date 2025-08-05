#include <cgl/inputcontroller.h>
#include <iostream>

CGL::InputController::InputController
(
    CGL::Context* context,
    CGL::Camera* camera
)
    : m_context(context)
{
    winHandler = context->handler();
    addSubscriber(camera);

    glfwSetKeyCallback(winHandler, &CGL::InputController::keyCallback);
    glfwSetCursorPosCallback(winHandler, &CGL::InputController::mouseCallback);
    glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CGL::InputController::process()
{
    glfwPollEvents();

    if (glfwGetKey(winHandler, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(winHandler, true);

    if (glfwGetKey(winHandler, GLFW_KEY_W) == GLFW_PRESS)
        keyNotify(CGL::Key_W);

    if (glfwGetKey(winHandler, GLFW_KEY_S) == GLFW_PRESS)
        keyNotify(CGL::Key_S);

    if (glfwGetKey(winHandler, GLFW_KEY_Q) == GLFW_PRESS)
        keyNotify(CGL::Key_Q);

    if (glfwGetKey(winHandler, GLFW_KEY_E) == GLFW_PRESS)
        keyNotify(CGL::Key_E);

    if (glfwGetKey(winHandler, GLFW_KEY_A) == GLFW_PRESS)
        keyNotify(CGL::Key_A);

    if (glfwGetKey(winHandler, GLFW_KEY_D) == GLFW_PRESS)
        keyNotify(CGL::Key_D);

    if (glfwGetKey(winHandler, GLFW_KEY_Z) == GLFW_PRESS)
        keyNotify(CGL::Key_Z);

    if (glfwGetKey(winHandler, GLFW_KEY_C) == GLFW_PRESS)
        keyNotify(CGL::Key_C);

    if (glfwGetKey(winHandler, GLFW_KEY_SPACE) == GLFW_PRESS && !keySpacePressed) {
        keySpacePressed = true;
    }

    if (glfwGetKey(winHandler, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        keySpacePressed = false;
    }
}

void CGL::InputController::keyNotify(const CGL::KeyType &keyType)
{
    for (auto obj: m_objects) {
        obj->keyEventHandler(KeyEvent(keyType));
    }
}

void CGL::InputController::mouseNotify(const CGL::MouseType &mouseType)
{
    for (auto obj: m_objects) {
        obj->mouseEventHandler(MouseEvent(mouseType));
    }
}

void CGL::InputController::mouseNotify(int dx, int dy)
{
    for (auto obj: m_objects) {
        obj->mouseEventHandler(MouseEvent(dx, dy));
    }
}

void CGL::InputController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int modes)
{
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        static bool cursorEnabled = true;
        if (cursorEnabled) {
            glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        cursorEnabled = !cursorEnabled;

        keyNotify(Key_B);
    }
}

void CGL::InputController::mouseCallback(GLFWwindow* window, double x, double y)
{
    mouseNotify(x, y);
}

void CGL::InputController::addSubscriber(Object *object)
{
    m_objects.push_back(object);
}

bool CGL::InputController::isKeySpacePressed() const
{
    return keySpacePressed;
}
