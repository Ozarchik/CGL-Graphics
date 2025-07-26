#ifndef BLEND_H
#define BLEND_H

#include <cgl/shader.h>
#include <cgl/scene.h>
#include <cgl/window.h>
#include <cgl/camera.h>
#include <cgl/texture/texturebase.h>

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
