#include <cgl/mesh/common/mesh.h>

CGL::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures, const std::vector<unsigned int>& indices)
    : m_buffer(vertices, textures, indices)
{}

void CGL::Mesh::setPrimitiveType(GLenum type)
{
    m_primitiveType = type;
}

void CGL::Mesh::setup()
{

}

void CGL::Mesh::draw(Shader &shader) {
    m_buffer.bind(&shader);
    glDrawElements(m_primitiveType, static_cast<unsigned int>(m_buffer.indices.size()), GL_UNSIGNED_INT, 0);

    m_buffer.unbind();
}

void CGL::Mesh::addTexture(const std::vector<TextureBase>& textures)
{
    m_buffer.setTextures(textures);
}
