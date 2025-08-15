#ifndef CGL_CUBE_H
#define CGL_CUBE_H

#include <cgl/graphics/mesh/common/mesh.h>

namespace CGL {
class Cube: public Mesh {
public:
    Cube();
    ~Cube();

    void draw(Shader& shader);
};
}

#endif
