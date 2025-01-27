#include "window.h"
#include <iostream>

CGL::Window::Window()
{

}

void CGL::Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	if (!m_window) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		std::abort();
	}

	glfwMakeContextCurrent(m_window);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	m_alive = true;
}

CGL::Window::~Window()
{
	glfwTerminate();
}

CGL::Window::width() const
{
	return m_width;
}

CGL::Window::height() const
{
	return m_height;
}

GLFWwindow* CGL::Window::getWindow() const
{
	return m_window;
}

void CGL::Window::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool CGL::Window::alive()
{
	return m_alive;
}

// void CGL::Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }
