#ifndef CGL_MESHBUILDER_H
#define CGL_MESHBUILDER_H

#include <cgl/graphics/mesh/common/mesh.h>
#include <vector>
#include <cgl/graphics/vertex/vertex.h>

namespace CGL {
class MeshBuilder
{
public:
    enum class MeshType {
        Mesh,
        Rectangle,
        Terrain,
        Sphere,
        Cube,
        Line
    };

    static MeshBuilder build(MeshType meshType);

    MeshBuilder& bind();
    MeshBuilder& setPrimitiveData(PrimitiveData data);
    std::shared_ptr<Mesh> done();
    
    CGL::MeshBuilder &setVAO(std::shared_ptr<VAOBuffer> vao);

private:
    MeshBuilder(const MeshType &meshType);

private:
    std::shared_ptr<Mesh> m_mesh;
};
}

#endif // CGL_MESHBUILDER_H
