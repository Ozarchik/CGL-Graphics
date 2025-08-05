#include <cgl/context.h>
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

	// setCursorEnabled(true);
	glfwMakeContextCurrent(m_window);

	m_alive = true;

    glEnable(GL_DEPTH_TEST);
}

CGL::Context::~Context()
{
	glfwTerminate();
}

void CGL::Context::setCursorEnabled(bool enabled)
{
	if (enabled) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

int CGL::Context::width() const
{
	return m_width;
}

void CGL::Context::setWidth(int width)
{
	m_width = width;
}

int CGL::Context::height() const
{
	return m_height;
}

void CGL::Context::setHeight(int height)
{
	m_height = height;
}

float CGL::Context::aspect() const
{
    return m_width/m_height;
}

float CGL::Context::deltaTime() const
{
    static float lastFrame = 0.0f;

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return deltaTime;
}

GLFWwindow* CGL::Context::handler() const
{
	return m_window;
}

void CGL::Context::update()
{
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CGL::Context::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::Context::alive()
{
	return m_alive;
}

// void CGL::Context::framebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }
