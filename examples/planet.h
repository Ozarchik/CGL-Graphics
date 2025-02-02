#ifndef PLANET_H
#define PLANET_H

#include "shader.h"
#include "scene.h"
#include "model.h"

namespace CGL {
class Planet
{
public:
    Planet();
    void use(const Transform &model, const Transform &view, const Transform &projection);

private:
    CGL::Shader m_shader;
    CGL::Shader m_shaderInst;
    CGL::Scene m_scene;
    CGL::Model m_planet;
    CGL::Model m_rock;
};
}

#endif // PLANET_H
