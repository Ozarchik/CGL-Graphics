#include <cgl/node.h>

CGL::Node::Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    m_renders.push_back(CGL::MeshRenderer{mesh});
}

CGL::Node::Node(std::vector<Mesh *> meshes, Shader &shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    for (int i = 0; i < meshes.size(); i++) {
        m_renders.push_back(CGL::MeshRenderer{meshes[i]});
    }
}

CGL::Node::Node(Shader &shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{

}

CGL::Node::~Node()
{
    for (auto& render: m_renders) {
        delete render.m_mesh;
    }
}

void CGL::Node::addMesh(Mesh *mesh, const Material &material)
{
    m_renders.emplace_back(mesh, material);
}

void CGL::Node::setTransform(const CGL::Transform& transform)
{
    m_transform = transform;
}

void CGL::Node::setPrimitiveType(GLenum type)
{
    for (auto& render: m_renders) {
        render.m_mesh->setPrimitiveType(type);
    }
}

void CGL::Node::update(CGL::Camera& camera, const Transform &parentTransform)
{
    CGL::Transform localTransform = parentTransform * m_transform;

    m_shader.use();
    m_shader.setMat4("model", localTransform);
    m_shader.setMat4("view", camera.getView());
    m_shader.setMat4("projection", camera.getProjection());

    for (auto& render: m_renders) {
        render.m_material.draw(m_shader);
        render.m_mesh->draw(m_shader);
    }

    for (const auto child: m_childs) {
        child->update(camera, localTransform);
    }
}
