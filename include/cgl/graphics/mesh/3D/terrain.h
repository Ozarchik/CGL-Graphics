#ifndef CGL_TERRAIN_H
#define CGL_TERRAIN_H

#include <cgl/graphics/mesh/common/mesh.h>

namespace CGL {
class Terrain: public CGL::Mesh
{
public:
    Terrain();

    void draw(CGL::Shader& shader) override;
};
}

#endif // CGL_TERRAIN_H
