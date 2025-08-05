#ifndef CGL_CONTEXT_H
#define CGL_CONTEXT_H

#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace CGL {

class Context {
public:
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
    
    float aspect() const;
    float deltaTime() const;

    GLFWwindow* handler() const;

private:
    GLFWwindow* m_window = nullptr;
    std::string m_title = "Test Project";

    int m_width = 1000;
    int m_height = 800;
	bool m_alive = false;
};
}

#endif
