#include "inputcontroller.h"

void processInput();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double x, double y);

CGL::InputController::InputController(
    CGL::Window* window,
    CGL::Camera* camera
)
    : m_window(window->getWindow())
{
    m_camera = camera;
    glfwSetFramebufferSizeCallback(m_window, &CGL::InputController::framebufferSizeCallback);
    glfwSetCursorPosCallback(m_window, &CGL::InputController::mouseCallback);
}

void CGL::InputController::process()
{
    // static_assert(m_window != nullptr, "glfw m_window is not valid (null)");

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->stepFront();

    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->stepBack();

    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->stepLeft();

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->stepRight();

    if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
        m_camera->stepDown();

    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
        m_camera->stepUp();
}

void CGL::InputController::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CGL::InputController::mouseCallback(GLFWwindow* window, double x, double y)
{
    m_camera->rotate(x, y);
}
