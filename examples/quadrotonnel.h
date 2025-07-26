#ifndef QUADROTONNEL_H
#define QUADROTONNEL_H

#include <cgl/scene.h>
#include <cgl/shader.h>
#include <cgl/window.h>
#include <cgl/camera.h>

namespace CGL {
class QuadroTonel
{
public:
    QuadroTonel();
    void use(Transform &model, Transform &view, Transform &projection);

private:
    CGL::Scene m_scene;
    CGL::Shader m_shader;
};
}

#endif // QUADROTONNEL_H
