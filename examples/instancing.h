#ifndef INSTANCING_H
#define INSTANCING_H

#include <cgl/shader.h>
#include <cgl/scene.h>

namespace CGL {
class Instancing
{
public:
    Instancing();

    void use(const Transform &model, const Transform &view, const Transform &projection);

private:
    CGL::Shader m_shader;
    CGL::Scene m_scene;
};
}

#endif // INSTANCING_H
