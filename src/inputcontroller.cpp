#include "inputcontroller.h"
#include <iostream>

CGL::InputController::InputController
(
    CGL::Window* window,
    CGL::Camera* camera
)
{
    m_window = window->getWindow();
    // m_camera = camera;

    addSubscriber(camera);

    glfwSetCursorPosCallback(m_window, &CGL::InputController::mouseCallback);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(window->getWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
}

void CGL::InputController::process()
{
    // static_assert(m_window != nullptr, "glfw m_window is not valid (null)");

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        keyNotify(CGL::Key_W);

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        keyNotify(CGL::Key_S);

    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        keyNotify(CGL::Key_A);

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        keyNotify(CGL::Key_D);

    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
        keyNotify(CGL::Key_Z);

    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
        keyNotify(CGL::Key_C);

    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS && !keySpacePressed) {
        keySpacePressed = true;
    }

    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
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

void CGL::InputController::mouseCallback(GLFWwindow* window, double x, double y)
{
    mouseNotify(x, y);
}

void CGL::InputController::resetStates()
{
    // keySpacePressed = false;
}

void CGL::InputController::addSubscriber(Object *object)
{
    m_objects.push_back(object);
}

bool CGL::InputController::isKeySpacePressed() const
{
    return keySpacePressed;
}
