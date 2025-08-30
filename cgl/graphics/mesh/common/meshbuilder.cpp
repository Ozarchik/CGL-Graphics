#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>

cgl::MeshBuilder::MeshBuilder(const MeshType& meshType)
{
    switch (meshType) {
    case MeshType::Rectangle: {
        m_mesh = std::make_shared<cgl::Rectangle>();
    } break;
    case MeshType::Sphere: {
        m_mesh = std::make_shared<cgl::Sphere>();
    } break;
    case MeshType::Cube: {
        m_mesh = std::make_shared<cgl::Cube>();
    } break;
    case MeshType::Line: {
        m_mesh = std::make_shared<cgl::Line>();
    } break;
    case MeshType::Mesh: {
        m_mesh = std::make_shared<cgl::Mesh>();
    } break;
    case MeshType::Terrain: {
        m_mesh = std::make_shared<cgl::Terrain>();
    } break;
    default: {
        m_mesh = std::make_shared<cgl::Mesh>();
    }
    }    
}

cgl::MeshBuilder cgl::MeshBuilder::build(MeshType meshType)
{
    return MeshBuilder(meshType);
}

cgl::MeshBuilder &cgl::MeshBuilder::bind()
{
    return *this;
}

std::shared_ptr<cgl::Mesh> cgl::MeshBuilder::done()
{
    return m_mesh;
}

cgl::MeshBuilder &cgl::MeshBuilder::setPrimitiveData(PrimitiveData data)
{
    m_mesh->setPrimitiveData(data);
    return *this;
}

cgl::MeshBuilder &cgl::MeshBuilder::setVAO(std::unique_ptr<cgl::VAOBuffer> vao)
{
    // m_mesh->setVAO(std::move(vao));
    m_mesh->setVAO(std::move(vao));
    return *this;
}
