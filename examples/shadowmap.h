#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "shader.h"
#include "scene.h"
#include "window.h"
#include "camera.h"

namespace CGL {
class ShadowMap
{
public:
    ShadowMap();
    void use(const Window &window, const Camera &camera);

private:
    CGL::Shader m_shader;
    CGL::Scene m_scene;
};
}

#endif // SHADOWMAP_H
