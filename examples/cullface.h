#ifndef CULLFACE_H
#define CULLFACE_H

#include "scene.h"
#include "window.h"
#include "camera.h"

namespace CGL {
class CullFace
{
public:
    CullFace();

    void use(const CGL::Window &window, const CGL::Camera &camera);

private:
    CGL::Scene m_scene;
    CGL::Shader m_shader;
};
}

#endif // CULLFACE_H
