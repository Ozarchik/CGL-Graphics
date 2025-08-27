#ifndef CGL_CORECONTEXT_H
#define CGL_CORECONTEXT_H

#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <cgl/tools/logger.h>
#include <cgl/tools/backtrace.h>

namespace CGL {

class CoreContext {
public:
    enum class BuffersToClear {
        NoClear = 0,
        Color = GL_COLOR_BUFFER_BIT,
        Depth = GL_DEPTH_BUFFER_BIT,
        Stecil = GL_STENCIL_BUFFER_BIT,
        All = Color | Depth | Stecil
    };

    enum class BufferCheckFunction {
        Never = GL_NEVER,
        Always = GL_ALWAYS,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Less = GL_LESS,
        LessEqual = GL_LEQUAL,
        Great = GL_GREATER,
        GreatEqual = GL_GEQUAL,
    };

    enum class CullFaceMode {
        Front = GL_FRONT,
        Back = GL_BACK,
        All = GL_FRONT_AND_BACK
    };

    ~CoreContext();
    CoreContext(const CoreContext& other) = delete;
    CoreContext& operator=(const CoreContext& other) = delete;

    CoreContext(CoreContext&& other) = delete;
    CoreContext& operator=(CoreContext&& other) = delete;

    void init();

    void update();
    void swapBuffers();

    bool isAlive();
    void setCursorEnabled(bool enabled);

	int width() const;
    void setWidth(int width);

	int height() const;
    void setHeight(int height);

    void setViewport(glm::vec4 rect);
    glm::vec4 viewport() const;

    void setCullFaceEnable(bool enabled);
    void setCullFaceMode(CullFaceMode mode);
    void setStencilEnable(bool enabled);
    void setStencilMask(unsigned char mask);
    void setStencilFunction(BufferCheckFunction function);
    void setDepthEnable(bool enabled);
    void setDepthFunction(BufferCheckFunction function);
    void setDepthWriteMode(bool mode);
    void setBuffersToClear(const BuffersToClear& buffersToClear);
    void setBackgroundColor(const glm::vec4& backgroundColor);

    float aspect() const;
    float deltaTime() const;

    GLFWwindow* handler() const;

    static CoreContext& instance();

    void setVsync(bool mode);
    bool vsync() const;

    void calcDeltaTime();

private:
    CoreContext();

private:
    GLFWwindow* m_window = nullptr;
    bool m_alive = false;

    std::string m_title = "Test Project";

    int m_width = 1200;
    int m_height = 800;
    unsigned char m_stencilMask = 0x00;
    bool m_cullfaceEnable = false;
    CullFaceMode m_cullfaceMode = CullFaceMode::Front;
    bool m_depthEnable = false;
    bool m_stencilEnable = false;
    bool m_depthWriteMode = false;
    bool m_vsync = false;
    bool m_cursorEnabled = false;

    BufferCheckFunction m_depthFunction = BufferCheckFunction::Less;
    BufferCheckFunction m_stencilFunction = BufferCheckFunction::Less;
    BuffersToClear m_buffersToClear;
    glm::vec4 m_backgroundColor;
    float m_deltaTime = 0.0f;
};

CoreContext& cglCoreContext();
}

#endif
