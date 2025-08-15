#ifndef CGL_SCENE_H
#define CGL_SCENE_H

#include <vector>
#include <cgl/graphics/scene/node.h>
#include <cgl/graphics/shader.h>
#include <cgl/core/camera.h>

namespace CGL {
class Scene {
public:
    Scene() = default;
    ~Scene();
    void render(CGL::Camera& camera);
    void append(Node* node);
    void clear();

    void setSelectedNode(Node* node);
    void unselectNode();
    Node* selectedNode() const;

    std::vector<Node*> nodes() const;
    
private:
    std::vector<Node*> m_nodes;
    Node* m_selectedNode = nullptr;
};
}

#endif
