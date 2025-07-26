#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include <cgl/transform.h>
#include <cgl/shader.h>
#include <cgl/scene.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/camera.h>

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
