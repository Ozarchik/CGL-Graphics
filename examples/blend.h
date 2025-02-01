#ifndef BLEND_H
#define BLEND_H

#include "shader.h"
#include "scene.h"
#include "window.h"
#include "camera.h"
#include "texturebase.h"

namespace CGL {
class Blend
{
public:
    Blend();

    void use(const CGL::Window &window, const CGL::Camera &camera);

private:
    CGL::Shader m_shader;
    CGL::Scene m_scene;

    CGL::TextureBase m_texture;
};
}

#endif // BLEND_H
