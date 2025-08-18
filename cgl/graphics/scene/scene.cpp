#include <cgl/graphics/scene/scene.h>

CGL::Scene::~Scene()
{
    clear();
}

void CGL::Scene::render(CGL::Camera& camera)
{
    for (const auto& node: m_nodes) {
        node->update(camera);
    }
}

void CGL::Scene::append(const std::shared_ptr<Node>& node)
{
    if (!node)
        return;

    m_nodes.push_back(node);
}

void CGL::Scene::clear()
{
    m_nodes.clear();
}

void CGL::Scene::setSelectedNode(Node *node)
{
    if (node)
        m_selectedNode = node;
}

void CGL::Scene::unselectNode()
{
    m_selectedNode = std::nullopt;
}

std::optional<CGL::Node*> CGL::Scene::selectedNode() const
{
    return m_selectedNode;
}

std::vector<std::shared_ptr<CGL::Node>> CGL::Scene::nodes() const
{
    return m_nodes;
}
