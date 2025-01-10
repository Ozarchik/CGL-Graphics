#include "context.h"
#include <iostream>

CGL::Context::Context()
{

}

void CGL::Context::init()
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

CGL::Context::~Context()
{
	glfwTerminate();
}

CGL::Context::width() const
{
	return m_width;
}

CGL::Context::height() const
{
	return m_height;
}

GLFWwindow* CGL::Context::getWindow() const
{
	return m_window;
}

void CGL::Context::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool CGL::Context::alive()
{
	return m_alive;
}