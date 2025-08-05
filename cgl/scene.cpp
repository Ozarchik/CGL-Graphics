#include <cgl/scene.h>

CGL::Scene::~Scene()
{
    clear();
}

void CGL::Scene::render(CGL::Camera& camera,
    CGL::Transform& model,
    CGL::Transform& view,
    CGL::Transform& projection
)
{
    // shader.use();

    for (const auto node: m_nodes) {
        node->update(camera, model, view, projection);
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
