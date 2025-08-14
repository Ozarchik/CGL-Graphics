#ifndef CGL_LINE_H
#define CGL_LINE_H

#include <cgl/mesh/common/mesh.h>

namespace CGL {
class Line: public CGL::Mesh
{
public:
    Line();

    void draw(CGL::Shader& shader) override;
};
}

#endif // CGL_LINE_H
