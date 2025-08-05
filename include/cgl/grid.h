#ifndef CGL_GRID_H
#define CGL_GRID_H

#include <cgl/scene.h>
#include <cgl/camera.h>
#include <cgl/mesh/3D/cube.h>

namespace CGL {
class Grid {

public:
    Grid();
    void draw(CGL::Camera& camera, CGL::Transform  model, CGL::Transform view, CGL::Transform projection);

private:
    int sideSize = 10;
    int cellSize = 1;
    CGL::Shader m_shader;
    CGL::Shader m_lightShader;
    CGL::Scene m_scene;
};
}

#endif // GRID_H
