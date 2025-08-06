#include <cgl/mesh/common/meshbuilder.h>

void CGL::MeshBuilder::setVertices(const std::vector<CGL::Vertex>& vertices)
{
    m_vertices = vertices;
}

void CGL::MeshBuilder::setIndices(const std::vector<unsigned int>& indices)
{
    m_indices = indices;
}

void CGL::MeshBuilder::setTextures(const std::vector<CGL::TextureBase>& textures)
{
    m_textures = textures;
}

CGL::Mesh CGL::MeshBuilder::build()
{
    CGL::Mesh mesh = CGL::Mesh(m_vertices, m_indices);
    return mesh;
}
