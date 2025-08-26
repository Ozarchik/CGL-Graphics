#ifndef CGL_GRID_H
#define CGL_GRID_H

#include <cgl/core/camera.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/mesh/3D/cube.h>

namespace CGL {
class Grid {

public:
    Grid();
    void draw(CGL::Camera& camera, CGL::Transform  model);

private:
    int sideSize = 2;
    int cellSize = 1;
    CGL::Shader m_lightShader;
    CGL::Scene m_scene;
};
}

#endif // GRID_H
