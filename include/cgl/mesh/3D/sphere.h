#ifndef SPHERE_H
#define SPHERE_H

#include <cgl/mesh/common/mesh.h>

namespace CGL {
class Sphere : public CGL::Mesh
{
public:
    Sphere();

    void draw(Shader& shader) override;
};
}

#endif // SPHERE_H
