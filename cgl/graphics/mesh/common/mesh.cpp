#include <cgl/graphics/mesh/common/mesh.h>

CGL::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_buffer(vertices, indices)
{
    m_primitiveData.type = CGL::RenderContext::Triangle;
    m_primitiveData.drawType = CGL::RenderContext::Indexes;
    m_primitiveData.size = m_buffer.m_indices.size();
    m_primitiveData.offset = 0;
}

void CGL::Mesh::setup()
{

}

void CGL::Mesh::draw(Shader &shader) {
    m_buffer.bind();
    RenderContext::instance().render(m_primitiveData);
    m_buffer.unbind();
}

CGL::BoundingBox CGL::Mesh::boundingBox() const
{
    CGL::BoundingBox box;

    if (m_buffer.m_vertices.empty())
        return { glm::vec3(0), glm::vec3(0) };

    box.min = m_buffer.m_vertices[0].position;
    box.max = m_buffer.m_vertices[0].position;

    for (const auto& vert: m_buffer.m_vertices) {
        box.min = glm::min(box.min, vert.position);
        box.max = glm::max(box.max, vert.position);
    }

    return box;
}

void CGL::Mesh::setVAO(std::shared_ptr<VAOBuffer> vao)
{
    // m_buffer.setVAO(std::move(vao));
    m_buffer.setVAO(vao);
}

void CGL::Mesh::setPrimitiveData(PrimitiveData data)
{
    m_primitiveData = data;
}

void CGL::Mesh::setPrimitiveType(CGL::RenderContext::Primitive type)
{
    m_primitiveData.type = type;
}
