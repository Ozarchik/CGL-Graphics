#ifndef CGL_TERRAIN_H
#define CGL_TERRAIN_H

#include <cgl/graphics/mesh/common/mesh.h>

namespace cgl {
class Terrain: public cgl::Mesh
{
public:
    Terrain();

    void draw(cgl::Shader& shader) override;
};
}

#endif // CGL_TERRAIN_H
