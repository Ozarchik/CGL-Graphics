#ifndef QUADROTONNEL_H
#define QUADROTONNEL_H

#include "scene.h"
#include "shader.h"
#include "window.h"
#include "camera.h"

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
