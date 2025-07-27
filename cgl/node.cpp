#include <cgl/node.h>

void CGL::Node::update(CGL::Shader& shader)
{
    // TODO: need implement

    for (const auto& mesh: m_meshes) {
        mesh->draw(shader);
    }

    for (const auto child: m_childs) {
        child->update(shader);
    }
}

void CGL::Node::addMesh(CGL::Mesh* mesh)
{
    m_meshes.push_back(mesh);
}