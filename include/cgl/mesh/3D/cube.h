#pragma once

// #include <cgl/mesh/common/mesh.h>
#include <cgl/mesh/common/mesh.h>

namespace CGL {
class Cube: public Mesh {
public:
    Cube();
    ~Cube();

    void draw(Shader& Shader);
};
}
