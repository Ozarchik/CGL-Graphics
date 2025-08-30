#ifndef CGL_NORMALMAP_H
#define CGL_NORMALMAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cgl/graphics/shader.h>
#include <cgl/core/camera.h>
#include <cgl/core/corecontext.h>

#include <memory>

namespace cgl {
enum PrimitiveType {
    Triangle
};

class NormalMap
{
public:
    NormalMap(cgl::CoreContext* window, Camera *camera);
    void use();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int tex;
    unsigned int normalMap;
    std::shared_ptr<cgl::Shader> m_shader;
    cgl::Camera* m_camera;
    cgl::CoreContext* m_context;
};
}

#endif // CGL_NORMALMAP_H
