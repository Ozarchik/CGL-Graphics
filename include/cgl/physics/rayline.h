#ifndef CGL_RAYLINE_H
#define CGL_RAYLINE_H

#include <cgl/graphics/shader.h>
#include <cgl/core/buffer/vaobuffer.h>
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

    glm::vec3 from, to;
    glm::vec3 line[2];

    std::unique_ptr<VAOBuffer> m_vao;
};
}

#endif // CGL_RAYLINE_H
