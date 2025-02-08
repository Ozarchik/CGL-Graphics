#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

namespace CGL {
class Sphere : public CGL::Mesh
{
public:
    Sphere();
    Sphere(const CGL::TextureBase& texture);

    void draw(Shader& shader) override;
};
}

#endif // SPHERE_H
