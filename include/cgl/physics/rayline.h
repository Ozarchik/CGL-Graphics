#ifndef CGL_RAYLINE_H
#define CGL_RAYLINE_H

#include <cgl/shader.h>
#include <cgl/camera.h>

namespace CGL {
class RayLine
{
public:
    RayLine(CGL::Camera& camera);

    void draw();
    void update(glm::vec3 origin, glm::vec3 direction, float length = 100.0f);

private:
    CGL::Camera& m_camera;
    CGL::Shader m_shader;

    GLuint VAO = 0, VBO = 0;
    glm::vec3 from, to;
    glm::vec3 line[2];
};
}

#endif // CGL_RAYLINE_H
