#include <cgl/mesh/common/mesh.h>

CGL::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_buffer(vertices, indices)
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

CGL::BoundingBox CGL::Mesh::boundingBox() const
{
    CGL::BoundingBox box;

    if (m_buffer.vertices.empty())
        return { glm::vec3(0), glm::vec3(0) };

    box.min = m_buffer.vertices[0].position;
    box.max = m_buffer.vertices[0].position;

    for (const auto& vert: m_buffer.vertices) {
        box.min = glm::min(box.min, vert.position);
        box.max = glm::max(box.max, vert.position);
    }

    return box;
}
