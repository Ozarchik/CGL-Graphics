#ifndef CGL_RENDERER_H
#define CGL_RENDERER_H

#include <cgl/graphics/grid.h>
#include <cgl/physics/raycast.h>
#include <cgl/core/camera.h>
#include <cgl/core/engine.h>

namespace cgl {
class Renderer
{
public:
    Renderer();
    
    void render(cgl::Scene& scene, View &view);
private:
    void createTerrainExample();

private:
    cgl::Grid grid;
};
}

#endif // CGL_RENDERER_H
