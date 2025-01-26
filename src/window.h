#pragma once

#include <string>
#include <glfw/glfw3.h>
#include "inputcontroller.h"

namespace CGL {

class Window {
public:
    Window();
    ~Window();

	void update();
	bool alive();

	int width() const;
	int height() const;

	void init();

	GLFWwindow* getWindow() const;

private:
    GLFWwindow* m_window = nullptr;
    std::string m_title = "Test Project";

	int m_width = 800, m_height = 600;
	bool m_alive = false;
};
}
