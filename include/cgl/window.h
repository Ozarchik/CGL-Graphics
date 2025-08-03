#pragma once

#include <string>
#include <glfw/glfw3.h>

namespace CGL {

class Window {
public:
    Window();
    ~Window();

	void update();
    void swapBuffers();


	bool alive();

    void setCursorEnabled(bool enabled);

	int width() const;
    void setWidth(int width);

	int height() const;
    void setHeight(int height);
    
    float aspect() const;

	void init();

    GLFWwindow* handler() const;

    // static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    GLFWwindow* m_window = nullptr;
    std::string m_title = "Test Project";

    int m_width = 1000;
    int m_height = 800;
	bool m_alive = false;
};
}
