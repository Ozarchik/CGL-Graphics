#ifndef CGL_RAYLINE_H
#define CGL_RAYLINE_H

#include <cgl/graphics/shader.h>
#include <cgl/core/camera.h>
#include <memory>

namespace cgl {
class RayLine
{
public:
    RayLine(cgl::Camera& camera);

    void draw();
    void update(glm::vec3 origin, glm::vec3 direction, float length = 100.0f);

private:
    cgl::Camera& m_camera;
    std::shared_ptr<cgl::Shader> m_shader;

    GLuint VAO = 0, VBO = 0;
    glm::vec3 from, to;
    glm::vec3 line[2];
};
}

#endif // CGL_RAYLINE_H
