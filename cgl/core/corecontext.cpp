#include <cgl/core/corecontext.h>
#include <cgl/utility/logger.h>
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

    init();
}

CGL::CoreContext::~CoreContext()
{
	glfwTerminate();
}

void CGL::CoreContext::init()
{
    m_depthEnable = false;
    glDisable(GL_DEPTH_TEST);

    m_stencilEnable = false;
    glDisable(GL_STENCIL_TEST);

    m_depthWriteMode = false;
    glDepthMask(false);

    m_vsync = false;
    glfwSwapInterval(0);

    m_depthFunction = BufferCheckFunction::Less;
    glDepthFunc(GL_LESS);

    m_stencilMask = 0xff;
    glStencilMask(0xff);

    m_stencilFunction = BufferCheckFunction::Less;
    glStencilFunc(GL_LESS, 1, m_stencilMask);

    m_cullfaceEnable = true;
    glEnable(GL_CULL_FACE);

    m_cullfaceMode = CullFaceMode::Front;
    glCullFace((int)CullFaceMode::Front);

    m_cursorEnabled = false;
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    m_buffersToClear = BuffersToClear::All;
    m_backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void CGL::CoreContext::setCursorEnabled(bool enabled)
{
    if (m_cursorEnabled == enabled)
        return;

    m_cursorEnabled = enabled;

    if (m_cursorEnabled) {
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
}

int CGL::CoreContext::height() const
{
	return m_height;
}

void CGL::CoreContext::setHeight(int height)
{
	m_height = height;
}

void CGL::CoreContext::setCullFaceEnable(bool enabled)
{
    if (m_cullfaceEnable == enabled)
        return;

    m_cullfaceEnable = enabled;

    if (m_cullfaceEnable)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

void CGL::CoreContext::setDepthEnable(bool enabled)
{
    if (m_depthEnable == enabled)
        return;

    m_depthEnable = enabled;

    if (m_depthEnable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void CGL::CoreContext::setCullFaceMode(CullFaceMode mode)
{
    if (m_cullfaceMode == mode)
        return;

    m_cullfaceMode = mode;
    glCullFace((int)m_cullfaceMode);
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
    if (m_stencilEnable == enabled)
        return;

    m_stencilEnable = enabled;

    if (m_stencilEnable)
        glEnable(GL_STENCIL_TEST);
    else
        glDisable(GL_STENCIL_TEST);
}

void CGL::CoreContext::setStencilMask(unsigned char mask)
{
    if (m_stencilMask == mask)
        return;

    m_stencilMask = mask;

    glStencilMask(m_stencilMask);

}

void CGL::CoreContext::setStencilFunction(BufferCheckFunction function)
{
    if (m_stencilFunction == function)
        return;

    m_stencilFunction = function;
    glStencilFunc((int)m_stencilFunction, 1, m_stencilMask);
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

void CGL::CoreContext::setVsync(bool mode)
{
    if (m_vsync == mode)
        return;

    m_vsync = mode;

    if (m_vsync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

bool CGL::CoreContext::vsync() const
{
    return m_vsync;
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
    glClear((int)m_buffersToClear);
}

void CGL::CoreContext::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool CGL::CoreContext::isAlive()
{
	return m_alive;
}

CGL::CoreContext& CGL::cglCoreContext()
{
    return CGL::CoreContext::instance();
}
