#include <cgl/mesh/common/meshbuilder.h>
#include <cgl/mesh/meshes2D.h>
#include <cgl/mesh/meshes3D.h>

CGL::MeshBuilder::MeshBuilder(const MeshType& meshType)
    : m_meshType(meshType)
{

}

CGL::MeshBuilder CGL::MeshBuilder::build(MeshType meshType)
{
    return MeshBuilder(meshType);
}

CGL::MeshBuilder &CGL::MeshBuilder::bind()
{
    m_buffer.bind();
    return *this;
}

CGL::Mesh *CGL::MeshBuilder::done()
{
    m_buffer.unbind();

    CGL::Mesh* mesh = nullptr;

    switch (m_meshType) {
    case Rectangle: {
        mesh = new CGL::Rectangle();
    } break;
    case Sphere: {
        mesh = new CGL::Sphere();
    } break;
    case Cube: {
        mesh = new CGL::Cube();
    } break;
    case Line: {
        mesh = new CGL::Line();
    } break;
    case UserDefine: {
        mesh = new CGL::Mesh();
    } break;
    default: {
        mesh = new CGL::Mesh();
    }
    }

    return mesh;
}

CGL::MeshBuilder& CGL::MeshBuilder::addVertices(const std::vector<CGL::Vertex>& vertices)
{
    m_buffer.setVertices(vertices);
    return *this;
}

CGL::MeshBuilder &CGL::MeshBuilder::addIndices(const std::vector<unsigned int> &indices)
{
    m_buffer.setIndices(indices);
    return *this;
}
