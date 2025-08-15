#ifndef CGL_MESHBUILDER_H
#define CGL_MESHBUILDER_H

#include <cgl/graphics/mesh/common/mesh.h>
#include <vector>
#include <cgl/graphics/vertex/vertex.h>

namespace CGL {
class MeshBuilder
{
public:
    enum MeshType {
        Rectangle,
        Sphere,
        Cube,
        Line,
        UserDefine
    };


    static MeshBuilder build(MeshType meshType);

    MeshBuilder& bind();
    MeshBuilder& addVertices(const std::vector<Vertex>& vertices);
    MeshBuilder& addIndices(const std::vector<unsigned int>& indices);
    Mesh* done();

private:
    MeshBuilder(const MeshType &meshType);

private:
    MeshType m_meshType;
    MeshBuffer m_buffer;
    Mesh* m_mesh;
};
}

#endif // CGL_MESHBUILDER_H
