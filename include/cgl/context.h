#ifndef CGL_CONTEXT_H
#define CGL_CONTEXT_H

#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

namespace CGL {

class Context {
public:
    enum BuffersToClear {
        NoClear = 0,
        Color = GL_COLOR_BUFFER_BIT,
        Depth = GL_DEPTH_BUFFER_BIT,
        Stecil = GL_STENCIL_BUFFER_BIT,
        All = Color | Depth | Stecil
    };

    enum BufferCheckFunction {
        Never = GL_NEVER,
        Always = GL_ALWAYS,
        Equal = GL_EQUAL,
        NotEqual = GL_NOTEQUAL,
        Less = GL_LESS,
        LessEqual = GL_LEQUAL,
        Great = GL_GREATER,
        GreatEqual = GL_GEQUAL,
    };

    Context();
    ~Context();

    void update();
    void swapBuffers();

    bool isAlive();
    void setCursorEnabled(bool enabled);

	int width() const;
    void setWidth(int width);

	int height() const;
    void setHeight(int height);
    
    void setBuffersToClear(const BuffersToClear& buffersToClear);
    void setBackgroundColor(const glm::vec4& backgroundColor);

    float aspect() const;
    float deltaTime() const;

    GLFWwindow* handler() const;

private:
    void calcDeltaTime();

private:
    GLFWwindow* m_window = nullptr;
    std::string m_title = "Test Project";

    int m_width = 800;
    int m_height = 800;
	bool m_alive = false;

    BuffersToClear m_buffersToClear;
    glm::vec4 m_backgroundColor;
    float m_deltaTime = 0.0f;
};
}

#endif
