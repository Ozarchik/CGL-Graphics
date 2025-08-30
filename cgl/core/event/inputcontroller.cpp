#include <cgl/core/event/inputcontroller.h>
#include <cgl/core/engine.h>

cgl::InputController::InputController()
{
    winHandler = cgl::CoreContext::instance().handler();

    glfwSetKeyCallback(winHandler, &cgl::InputController::keyCallback);
    glfwSetCursorPosCallback(winHandler, &cgl::InputController::mouseCallback);
    glfwSetScrollCallback(winHandler, &cgl::InputController::scrollCallback);
    glfwSetMouseButtonCallback(winHandler, &cgl::InputController::mouseButtonCallback);
    // glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void cgl::InputController::process()
{
    glfwPollEvents();

    if (glfwGetKey(winHandler, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(winHandler, true);

    int modifiers = cgl::Key_None;
    if (glfwGetKey(winHandler, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(winHandler, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        modifiers = modifiers | cgl::Key_Shift;
    }
    if (glfwGetKey(winHandler, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
        glfwGetKey(winHandler, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
        modifiers = modifiers | cgl::Key_Ctrl;
    }
    if (glfwGetKey(winHandler, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(winHandler, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
        modifiers = modifiers | cgl::Key_Alt;
    }


    const std::vector<std::pair<int, KeyType>> letterKeys = {
        {GLFW_KEY_A, Key_A}/*, {GLFW_KEY_B, Key_B}*/, {GLFW_KEY_C, Key_C},
        {GLFW_KEY_D, Key_D}, {GLFW_KEY_E, Key_E}, {GLFW_KEY_F, Key_F},
        {GLFW_KEY_G, Key_G}, {GLFW_KEY_H, Key_H}, {GLFW_KEY_I, Key_I},
        {GLFW_KEY_J, Key_J}, {GLFW_KEY_K, Key_K}, {GLFW_KEY_L, Key_L},
        {GLFW_KEY_M, Key_M}, {GLFW_KEY_N, Key_N}, {GLFW_KEY_O, Key_O},
        {GLFW_KEY_P, Key_P}, {GLFW_KEY_Q, Key_Q}, {GLFW_KEY_R, Key_R},
        {GLFW_KEY_S, Key_S}, {GLFW_KEY_T, Key_T}, {GLFW_KEY_U, Key_U},
        {GLFW_KEY_V, Key_V}, {GLFW_KEY_W, Key_W}, {GLFW_KEY_X, Key_X},
        {GLFW_KEY_Y, Key_Y}, {GLFW_KEY_Z, Key_Z}
    };

    const std::vector<std::pair<int, KeyType>> numberKeys = {
        {GLFW_KEY_0, Key_0}, {GLFW_KEY_1, Key_1}, {GLFW_KEY_2, Key_2},
        {GLFW_KEY_3, Key_3}, {GLFW_KEY_4, Key_4}, {GLFW_KEY_5, Key_5},
        {GLFW_KEY_6, Key_6}, {GLFW_KEY_7, Key_7}, {GLFW_KEY_8, Key_8},
        {GLFW_KEY_9, Key_9}
    };

    const std::vector<std::pair<int, KeyType>> specialKeys = {
        {GLFW_KEY_SPACE, Key_Space}, {GLFW_KEY_ENTER, Key_Enter},
        {GLFW_KEY_TAB, Key_Tab}, {GLFW_KEY_BACKSPACE, Key_Backspace}
    };

    auto checkKeys = [=](const auto& keyMap) {
        for (const auto& [glfwKey, cglKey] : keyMap) {
            if (glfwGetKey(winHandler, glfwKey) == GLFW_PRESS) {
                keyNotify(cglKey, cgl::Key_Press, static_cast<KeyModifier>(modifiers));
            }
        }
    };

    checkKeys(letterKeys);
    checkKeys(numberKeys);
    checkKeys(specialKeys);

    if (glfwGetKey(winHandler, GLFW_KEY_SPACE) == GLFW_PRESS && !keySpacePressed) {
        keySpacePressed = true;
    }

    if (glfwGetKey(winHandler, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        keySpacePressed = false;
    }
}

void cgl::InputController::keyNotify(KeyType type, KeyAction action, KeyModifier modifier)
{
    for (auto obj: m_objects) {
        obj->keyEventHandler(KeyEvent(type, action, modifier));
    }

    cglEngine().activeCamera()->keyEventHandler(KeyEvent(type, action, modifier));
}

void cgl::InputController::mouseNotify(int dx, int dy, cgl::MouseState state)
{
    for (auto obj: m_objects) {
        obj->mouseEventHandler(MouseEvent(dx, dy, state));
    }

    cglEngine().activeCamera()->mouseEventHandler(MouseEvent(dx, dy, state));
}

void cgl::InputController::wheelNotify(double dx, double dy, MouseWheelState state)
{
    for (auto obj: m_objects) {
        obj->mouseWheelEventHandler(MouseWheelEvent(dx, dy, state));
    }
}

void cgl::InputController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int modes)
{
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        static bool cursorEnabled = true;
        if (cursorEnabled) {
            glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(winHandler, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        cursorEnabled = !cursorEnabled;

        keyNotify(Key_B, Key_Press, Key_None);
    }

    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        static bool firstCamera = false;
        if (firstCamera) {
            cglEngine().setActiveCamera(cglEngine().views().front().camera.get());
        } else {
            cglEngine().setActiveCamera(cglEngine().views().back().camera.get());
        }

        firstCamera = !firstCamera;

        keyNotify(Key_V, Key_Press, Key_None);
    }
}

void cgl::InputController::scrollCallback(GLFWwindow *window, double dx, double dy)
{
    if (dy < 0)
        wheelNotify(dx, dy, cgl::MouseWheelState{cgl::Down});
    else
        wheelNotify(dx, dy, cgl::MouseWheelState{cgl::Up});
}

void cgl::InputController::mouseCallback(GLFWwindow* window, double x, double y)
{
    m_mouseX = x;
    m_mouseY = y;

    mouseNotify(m_mouseX, m_mouseY);
}

void cgl::InputController::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_RELEASE) {
        mouseNotify(m_mouseX, m_mouseY, cgl::MouseState{cgl::Mouse_Release, cgl::Mouse_Left});
    }
}

void cgl::InputController::addSubscriber(Object *object)
{
    m_objects.push_back(object);
}

bool cgl::InputController::isKeySpacePressed() const
{
    return keySpacePressed;
}
