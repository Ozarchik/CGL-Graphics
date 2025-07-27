#ifndef FLOORGENERATOR_H
#define FLOORGENERATOR_H

#include <cgl/scene.h>
#include <cgl/camera.h>
#include <cgl/mesh/3D/cube.h>

namespace CGL {
class FloorGenerator {

public:
    FloorGenerator();
    void draw(CGL::Camera& camera, CGL::Transform  model, CGL::Transform view, CGL::Transform projection);

private:
    int sideSize = 10;
    int cellSize = 1;
    CGL::Scene m_scene;
    CGL::Shader m_shader;
    CGL::Shader m_lightShader;
    CGL::Cube* m_lightCube;
};
}

#endif // FLOORGENERATOR_H