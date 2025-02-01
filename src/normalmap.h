#ifndef NORMALMAP_H
#define NORMALMAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "camera.h"
#include "window.h"

namespace CGL {
enum PrimitiveType {
    Triangle
};

class NormalMap
{
public:
    NormalMap(CGL::Window* window, Camera *camera);
    void use();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int tex;
    unsigned int normalMap;
    CGL::Shader shader;
    CGL::Camera* camera;
    CGL::Window* window;
};
}

#endif // NORMALMAP_H
