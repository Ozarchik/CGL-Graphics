#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include "transform.h"
#include "shader.h"
#include "scene.h"
#include "cube.h"
#include "camera.h"

namespace CGL {
class LightScene
{
public:
    LightScene();
    void use(CGL::Camera &camera, CGL::Transform model, CGL::Transform view, CGL::Transform projection);
    void gammaOnOff();

private:
    CGL::Scene m_scene;
    CGL::Shader m_shader;
    CGL::Shader m_lightShader;
    CGL::Cube* m_lightCube;
};
}
#endif // LIGHTSCENE_H
