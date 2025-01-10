#include "mesh.h"

CGL::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<TextureBase>& textures, const std::vector<unsigned int>& indices)
    : m_vertices(vertices), m_textures(textures), m_indices(indices)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    this->setup();
}
