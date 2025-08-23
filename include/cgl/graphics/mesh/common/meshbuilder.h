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
    MeshBuilder& addVertices(const std::vector<Vertex>& vertices);
    MeshBuilder& addIndices(const std::vector<unsigned int>& indices);
    MeshBuilder& setPrimitiveData(PrimitiveData data);
    Mesh* done();

    CGL::MeshBuilder &setVAO(VAOBuffer &&vao);

private:
    MeshBuilder(const MeshType &meshType);

private:
    MeshType m_meshType;
    MeshBuffer m_buffer;
    Mesh* m_mesh = nullptr;
};
}

#endif // CGL_MESHBUILDER_H
