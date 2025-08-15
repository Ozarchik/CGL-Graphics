#ifndef CGL_NORMALMAP_H
#define CGL_NORMALMAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cgl/graphics/shader.h>
#include <cgl/core/camera.h>
#include <cgl/core/corecontext.h>

namespace CGL {
enum PrimitiveType {
    Triangle
};

class NormalMap
{
public:
    NormalMap(CGL::CoreContext* window, Camera *camera);
    void use();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int tex;
    unsigned int normalMap;
    CGL::Shader shader;
    CGL::Camera* m_camera;
    CGL::CoreContext* m_context;
};
}

#endif // CGL_NORMALMAP_H
