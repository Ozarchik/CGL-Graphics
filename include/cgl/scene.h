#pragma once
#include <vector>
#include <cgl/node.h>
#include <cgl/shader.h>
#include <cgl/camera.h>

namespace CGL {
class Scene {
public:
    Scene() = default;
    ~Scene();
    void render(CGL::Camera& camera);
    void append(Node* node);
    void clear();

    void setSelectedNode(Node* node);
    void upselectNode();
    Node* selectedNode() const;

    std::vector<Node*> nodes() const;
    
private:
    std::vector<Node*> m_nodes;
};
}
