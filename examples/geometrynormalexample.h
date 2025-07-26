#ifndef GEOMETRYNORMALEXAMPLE_H
#define GEOMETRYNORMALEXAMPLE_H

#include <examples/geometryexample.h>
#include <cgl/model/model.h>

namespace CGL {
class GeometryNormalExample : public GeometryExample
{
public:
    GeometryNormalExample();
    void use(const CGL::Transform& model, const Transform &view, const Transform &projection);
    CGL::Model object;
    CGL::Shader modelShader;
};
}

#endif // GEOMETRYNORMALEXAMPLE_H
