#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>
#include <cgl/utility/logger.h>

CGL::MeshBuilder::MeshBuilder(const MeshType& meshType)
    : m_meshType(meshType)
{
    switch (m_meshType) {
    case MeshType::Rectangle: {
        m_mesh = new CGL::Rectangle();
    } break;
    case MeshType::Sphere: {
        m_mesh = new CGL::Sphere();
    } break;
    case MeshType::Cube: {
        m_mesh = new CGL::Cube();
    } break;
    case MeshType::Line: {
        m_mesh = new CGL::Line();
    } break;
    case MeshType::Mesh: {
        m_mesh = new CGL::Mesh();
    } break;
    case MeshType::Terrain: {
        m_mesh = new CGL::Terrain();
    } break;
    default: {
        m_mesh = new CGL::Mesh();
    }
    }

    
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
    return m_mesh;
}

// CGL::MeshBuilder& CGL::MeshBuilder::addVertices(const std::vector<CGL::Vertex>& vertices)
// {
//     m_buffer.setVertices(vertices);
//     return *this;
// }

CGL::MeshBuilder &CGL::MeshBuilder::setPrimitiveData(PrimitiveData data)
{
    m_mesh->setPrimitiveData(data);
    return *this;
}

CGL::MeshBuilder &CGL::MeshBuilder::setVAO(CGL::VAOBuffer&& vao)
{
    m_buffer.setVAO(std::move(vao));
    return *this;
}
