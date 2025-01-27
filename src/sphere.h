#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

namespace CGL {
class Sphere : public CGL::Mesh
{
public:
    Sphere();

    void draw(Shader& shader) override;

private:
    std::vector<float> colors;
};
}

#endif // SPHERE_H
