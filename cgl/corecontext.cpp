#include <cgl/corecontext.h>
#include <cgl/application.h>
#include <iostream>


constexpr double aspect = 1200.0/800.0;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    CGL::Application::instance().draw();


    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glfwSwapBuffers(window);

    // float targetAspect = (float)LOGICAL_WIDTH / LOGICAL_HEIGHT;
    // float windowAspect = (float)width / height;
    // int offsetX = 0, offsetY = 0;

    // if (windowAspect > targetAspect) {
    //     viewportHeight = height;
    //     viewportWidth = (int)(height * targetAspect);
    //     offsetX = (width - viewportWidth) / 2;
    // } else {
    //     viewportWidth = width;
    //     viewportHeight = (int)(width / targetAspect);
    //     offsetY = (height - viewportHeight) / 2;
    // }

    // int viewportX = (width - viewportWidth) / 2;
    // int viewportY = (height - viewportHeight) / 2;
    // glViewport(0, 0, width, height);
    // glViewport(0, 0, 800, 800);
    // glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    // glViewport(0, 0, width, height);
}

CGL::CoreContext::CoreContext()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


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
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glViewport(0, 0, m_width, m_height);
}

CGL::CoreContext::~CoreContext()
{
	glfwTerminate();
}

void CGL::CoreContext::setCursorEnabled(bool enabled)
{
	if (enabled) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	} else {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

int CGL::CoreContext::width() const
{
	return m_width;
}

void CGL::CoreContext::setWidth(int width)
{
	m_width = width;
    glfwSetWindowSize(m_window, m_width, m_height);
}

int CGL::CoreContext::height() const
{
	return m_height;
}

void CGL::CoreContext::setHeight(int height)
{
	m_height = height;
    glfwSetWindowSize(m_window, m_width, m_height);
}

void CGL::CoreContext::setDepthEnable(bool enabled)
{
    if (enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void CGL::CoreContext::setDepthFunction(BufferCheckFunction function)
{
    m_depthFunction = function;
}

void CGL::CoreContext::setDepthWriteMode(bool mode)
{
    m_depthWriteMode = mode;
}

void CGL::CoreContext::setStencilEnable(bool enabled)
{
    if (enabled)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);
}

void CGL::CoreContext::setStencilMask(unsigned char mask)
{
    m_stencilMask = mask;
}

void CGL::CoreContext::setStencilFunction(BufferCheckFunction function)
{
    m_stencilFunction = function;
}

void CGL::CoreContext::setBuffersToClear(const BuffersToClear &buffersToClear)
{
    m_buffersToClear = buffersToClear;
}

void CGL::CoreContext::setBackgroundColor(const glm::vec4 &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

float CGL::CoreContext::aspect() const
{
    return m_width/m_height;
}

void CGL::CoreContext::calcDeltaTime()
{
    static float lastFrame = 0.0f;

    float currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float CGL::CoreContext::deltaTime() const
{
    return m_deltaTime;
}

GLFWwindow* CGL::CoreContext::handler() const
{
	return m_window;
}

CGL::CoreContext& CGL::CoreContext::instance()
{
    static CoreContext instance;
    return instance;
}

void CGL::CoreContext::update()
{
    if (glfwWindowShouldClose(m_window))
        m_alive = false;

    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    glClear(m_buffersToClear);
    glDepthFunc(m_depthFunction);
    glStencilFunc(m_stencilFunction, 1, 0xff);
    glStencilMask(m_stencilMask);

    calcDeltaTime();
}

void CGL::CoreContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::CoreContext::isAlive()
{
	return m_alive;
}
