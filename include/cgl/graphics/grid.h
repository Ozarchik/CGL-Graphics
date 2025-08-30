#ifndef CGL_GRID_H
#define CGL_GRID_H

#include <cgl/core/camera.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/mesh/3D/cube.h>

namespace cgl {
class Grid {

public:
    Grid();
    void draw(cgl::Camera& camera, cgl::Transform  model);

private:
    int sideSize = 2;
    int cellSize = 1;
    cgl::Shader m_lightShader;
    cgl::Scene m_scene;
};
}

#endif // GRID_H
