#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>

CGL::MeshBuilder::MeshBuilder(const MeshType& meshType)
{
    switch (meshType) {
    case MeshType::Rectangle: {
        m_mesh = std::make_shared<CGL::Rectangle>();
    } break;
    case MeshType::Sphere: {
        m_mesh = std::make_shared<CGL::Sphere>();
    } break;
    case MeshType::Cube: {
        m_mesh = std::make_shared<CGL::Cube>();
    } break;
    case MeshType::Line: {
        m_mesh = std::make_shared<CGL::Line>();
    } break;
    case MeshType::Mesh: {
        m_mesh = std::make_shared<CGL::Mesh>();
    } break;
    case MeshType::Terrain: {
        m_mesh = std::make_shared<CGL::Terrain>();
    } break;
    default: {
        m_mesh = std::make_shared<CGL::Mesh>();
    }
    }    
}

CGL::MeshBuilder CGL::MeshBuilder::build(MeshType meshType)
{
    return MeshBuilder(meshType);
}

CGL::MeshBuilder &CGL::MeshBuilder::bind()
{
    return *this;
}

std::shared_ptr<CGL::Mesh> CGL::MeshBuilder::done()
{
    return m_mesh;
}

CGL::MeshBuilder &CGL::MeshBuilder::setPrimitiveData(PrimitiveData data)
{
    m_mesh->setPrimitiveData(data);
    return *this;
}

CGL::MeshBuilder &CGL::MeshBuilder::setVAO(std::shared_ptr<CGL::VAOBuffer> vao)
{
    // m_mesh->setVAO(std::move(vao));
    m_mesh->setVAO(vao);
    return *this;
}
