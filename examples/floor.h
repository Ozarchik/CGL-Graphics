#ifndef FLOOR_H
#define FLOOR_H

#include "shader.h"
#include "window.h"
#include "camera.h"

namespace CGL {
class Floor
{
public:
    Floor();

    void use(const Window &window, const Camera &camera);

private:
    unsigned int floorVAO;
    unsigned int floorVBO;
    unsigned int floorTex;
    unsigned int brickTex;
    CGL::Shader m_shader;
};
}

#endif // FLOOR_H
