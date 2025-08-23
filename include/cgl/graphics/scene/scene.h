#ifndef CGL_SCENE_H
#define CGL_SCENE_H

#include <memory>
#include <vector>
#include <cgl/graphics/scene/node.h>
// #include <cgl/graphics/shader.h>
#include <cgl/core/camera.h>
#include <optional>

namespace CGL {
class Scene {
public:
    Scene() = default;
    ~Scene();
    void render(CGL::Camera& camera);
    void append(const std::shared_ptr<Node> &node);
    void clear();

    void setSelectedNode(Node* node);
    void unselectNode();
    std::optional<Node*> selectedNode() const;

    std::vector<std::shared_ptr<Node>> nodes() const;
    
private:
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::optional<Node*> m_selectedNode = std::nullopt;
};
}

#endif
