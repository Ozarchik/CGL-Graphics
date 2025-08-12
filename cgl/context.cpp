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
    // glViewport(0, 0, width, height);
    // glViewport(0, 0, 800, 800);
    // glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
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


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load GLAD" << std::endl;
        std::abort();
    }

    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    // glViewport(0, 0, width(), height());
    // glViewport(0, 0, 800, 800);
    // glEnable(GL_DEPTH_TEST);
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
    glfwSetWindowSize(m_window, m_width, m_height);
}

void CGL::Context::setBuffersToClear(const BuffersToClear &buffersToClear)
{
    m_buffersToClear = buffersToClear;
}

void CGL::Context::setBackgroundColor(const glm::vec4 &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

float CGL::Context::aspect() const
{
    return m_width/m_height;
}

void CGL::Context::calcDeltaTime()
{
    static float lastFrame = 0.0f;

    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float CGL::Context::deltaTime() const
{
    return m_deltaTime;
}

GLFWwindow* CGL::Context::handler() const
{
	return m_window;
}

void CGL::Context::update()
{
    if (glfwWindowShouldClose(m_window))
        m_alive = false;

    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    glClear(m_buffersToClear);

    setWidth(viewportWidth);
    setHeight(viewportHeight);
    calcDeltaTime();
}

void CGL::Context::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::Context::isAlive()
{
	return m_alive;
}
