#ifndef CGL_LINE_H
#define CGL_LINE_H

#include <cgl/graphics/mesh/common/mesh.h>

namespace cgl {
class Line: public cgl::Mesh
{
public:
    Line();

    void draw(cgl::Shader& shader) override;
};
}

#endif // CGL_LINE_H
