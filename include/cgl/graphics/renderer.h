#ifndef CGL_RENDERER_H
#define CGL_RENDERER_H

#include <cgl/graphics/grid.h>
#include <cgl/physics/raycast.h>
#include <cgl/core/camera.h>
#include <cgl/core/engine.h>

namespace CGL {
class Renderer
{
public:
    Renderer();
    
    void render(CGL::Scene& scene, View &view);
private:
    void createTerrainExample();

private:
    CGL::Grid grid;
};
}

#endif // CGL_RENDERER_H
