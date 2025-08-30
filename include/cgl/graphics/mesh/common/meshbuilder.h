#ifndef CGL_MESHBUILDER_H
#define CGL_MESHBUILDER_H

#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <cgl/graphics/vertex/vertex.h>
#include <memory>

namespace cgl {
class MeshBuilder
{
public:
    static MeshBuilder build(MeshType meshType);

    MeshBuilder& bind();
    MeshBuilder& setPrimitiveData(PrimitiveData data);
    std::shared_ptr<Mesh> done();
    
    cgl::MeshBuilder &setVAO(std::unique_ptr<VAOBuffer> vao);

private:
    MeshBuilder(const MeshType &meshType);

private:
    std::shared_ptr<Mesh> m_mesh;
};
}

#endif // CGL_MESHBUILDER_H
