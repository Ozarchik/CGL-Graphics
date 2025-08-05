#include <cgl/scene.h>

CGL::Scene::~Scene()
{
    clear();
}

void CGL::Scene::render(Shader& shader)
{
    shader.use();

    for (const auto node: m_nodes) {
        node->update();
    }
}

void CGL::Scene::append(Node* node)
{
    m_nodes.push_back(node);
}

void CGL::Scene::clear()
{
    for (auto node: m_nodes) {
        delete node;
    }

    m_nodes.clear();
}

std::vector<CGL::Node*> CGL::Scene::nodes() const
{
    return m_nodes;
}
