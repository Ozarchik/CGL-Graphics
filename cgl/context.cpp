#include <cgl/context.h>
#include <iostream>

const int LOGICAL_WIDTH = 800;
const int LOGICAL_HEIGHT = 600;
int viewportWidth = LOGICAL_WIDTH, viewportHeight = LOGICAL_HEIGHT;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    float targetAspect = (float)LOGICAL_WIDTH / LOGICAL_HEIGHT;
    float windowAspect = (float)width / height;
    int offsetX = 0, offsetY = 0;

    if (windowAspect > targetAspect) {
        viewportHeight = height;
        viewportWidth = (int)(height * targetAspect);
        offsetX = (width - viewportWidth) / 2;
    } else {
        viewportWidth = width;
        viewportHeight = (int)(width / targetAspect);
        offsetY = (height - viewportHeight) / 2;
    }

    int viewportX = (width - viewportWidth) / 2;
    int viewportY = (height - viewportHeight) / 2;
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    // glViewport(0, 0, width, height);
}

CGL::Context::Context()
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

    m_alive = true;


    initOpenGL();
    glEnable(GL_DEPTH_TEST);
}

void CGL::Context::initOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        std::abort();
    }

    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    glViewport(0, 0, width(), height());
}


void CGL::Context::init()
{
    return;

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
    if (glfwWindowShouldClose(m_window))
        m_alive = false;

	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    setWidth(viewportWidth);
    setHeight(viewportHeight);
}

void CGL::Context::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::Context::isAlive()
{
	return m_alive;
}

// void CGL::Context::framebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }
