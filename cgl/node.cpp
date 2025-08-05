#include <cgl/node.h>

CGL::Node::Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform)
    : m_shader(shader)
    , m_mesh(mesh)
    , m_transform(transform)
{
    
}

void CGL::Node::setTransform(const CGL::Transform& transform)
{
    m_transform = transform;
}

void CGL::Node::update()
{    
    m_shader.setMat4("model", m_transform);
    m_mesh->draw(m_shader);

    for (const auto child: m_childs) {
        child->update();
    }
}