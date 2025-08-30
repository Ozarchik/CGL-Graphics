#include <cgl/graphics/scene/scene.h>

cgl::Scene::~Scene()
{
    clear();
}

void cgl::Scene::render(cgl::Camera& camera)
{
    for (const auto& node: m_nodes) {
        node->update(camera);
    }
}

void cgl::Scene::append(const std::shared_ptr<Node>& node)
{
    if (!node)
        return;

    m_nodes.push_back(node);
}

void cgl::Scene::clear()
{
    m_nodes.clear();
}

void cgl::Scene::setSelectedNode(Node *node)
{
    if (node)
        m_selectedNode = node;
}

void cgl::Scene::unselectNode()
{
    m_selectedNode = std::nullopt;
}

std::optional<cgl::Node*> cgl::Scene::selectedNode() const
{
    return m_selectedNode;
}

std::vector<std::shared_ptr<cgl::Node>> cgl::Scene::nodes() const
{
    return m_nodes;
}
