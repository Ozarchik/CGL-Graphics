#include <cgl/window.h>
#include <iostream>

CGL::Window::Window()
{

}

void CGL::Window::init()
{
	glfwInit();
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	if (!m_window) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		std::abort();
	}

	// setCursorEnabled(true);
	glfwMakeContextCurrent(m_window);

	m_alive = true;
}

CGL::Window::~Window()
{
	glfwTerminate();
}

void CGL::Window::setCursorEnabled(bool enabled)
{
	if (enabled) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

CGL::Window::width() const
{
	return m_width;
}

CGL::Window::height() const
{
	return m_height;
}

float CGL::Window::aspect() const
{
    return m_width/m_height;
}

GLFWwindow* CGL::Window::handler() const
{
	return m_window;
}

void CGL::Window::update()
{
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CGL::Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::Window::alive()
{
	return m_alive;
}

// void CGL::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }
