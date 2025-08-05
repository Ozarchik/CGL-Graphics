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

void CGL::Node::update(CGL::Camera& camera,
   CGL::Transform& model,
   CGL::Transform& view,
   CGL::Transform& projection
)
{
    m_shader.use();
    m_shader.setMat4("model", m_transform);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);

    for (auto& mesh: m_meshes) {
        mesh->draw(m_shader);
    }

    for (const auto child: m_childs) {
        child->update(camera, model, view, projection);
    }
}
