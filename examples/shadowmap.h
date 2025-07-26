#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <cgl/shader.h>
#include <cgl/scene.h>
#include <cgl/window.h>
#include <cgl/camera.h>

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
