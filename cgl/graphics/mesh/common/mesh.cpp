#include <cgl/graphics/mesh/common/mesh.h>

cgl::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_buffer(vertices, indices)
{
    m_primitiveData.type = cgl::RenderContext::Triangle;
    m_primitiveData.drawType = cgl::RenderContext::Indexes;
    m_primitiveData.size = m_buffer.m_indices.size();
    m_primitiveData.offset = 0;
}

void cgl::Mesh::setup()
{

}

void cgl::Mesh::draw(Shader &shader) {
    m_buffer.bind();
    RenderContext::instance().render(m_primitiveData);
    m_buffer.unbind();
}

cgl::BoundingBox cgl::Mesh::boundingBox() const
{
    cgl::BoundingBox box;

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

void cgl::Mesh::setVAO(std::unique_ptr<VAOBuffer>&& vao)
{
    // m_buffer.setVAO(std::move(vao));
    m_buffer.setVAO(std::move(vao));
}

void cgl::Mesh::setPrimitiveData(PrimitiveData data)
{
    m_primitiveData = data;
}

void cgl::Mesh::setPrimitiveType(cgl::RenderContext::Primitive type)
{
    m_primitiveData.type = type;
}
