#ifndef CGL_SPHERE_H
#define CGL_SPHERE_H

#include <cgl/graphics/mesh/common/mesh.h>

namespace cgl {
class Sphere : public cgl::Mesh
{
public:
    Sphere();

    void draw(Shader& shader) override;
};
}

#endif // CGL_SPHERE_H
