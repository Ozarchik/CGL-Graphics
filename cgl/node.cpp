#include <cgl/node.h>

CGL::Node::Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform)
    : m_shader(shader)
    , m_meshes{mesh}
    , m_transform(transform)
{
    
}

CGL::Node::Node(std::vector<Mesh *> meshes, Shader &shader, Transform transform)
    : m_shader(shader)
    , m_meshes(meshes)
    , m_transform(transform)
{

}

CGL::Node::~Node()
{
    for (auto& mesh: m_meshes) {
        delete mesh;
    }
}

void CGL::Node::setTransform(const CGL::Transform& transform)
{
    m_transform = transform;
}

void CGL::Node::setPrimitiveType(GLenum type)
{
    for (auto& mesh: m_meshes) {
        mesh->setPrimitiveType(type);
    }
}

void CGL::Node::update(CGL::Camera& camera, const Transform &parentTransform)
{
    m_shader.use();
    CGL::Transform localTransform = m_transform * parentTransform;
    m_shader.setMat4("model", /*localTransform*/m_transform);
    m_shader.setMat4("view", camera.getView());
    m_shader.setMat4("projection", camera.getProjection());

    for (auto& mesh: m_meshes) {
        mesh->draw(m_shader);
    }

    for (const auto child: m_childs) {
        child->update(camera, model, view, projection);
    }
}
