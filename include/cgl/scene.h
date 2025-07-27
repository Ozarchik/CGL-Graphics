#pragma once
#include <vector>
#include <cgl/node.h>
#include <cgl/shader.h>

namespace CGL {
class Scene {
public:
    Scene() = default;
    ~Scene();
    void render(Shader& shader);
    void append(Node* node);
    void clear();
    std::vector<Node*> nodes() const;
    
private:
    std::vector<Node*> m_nodes;
};
}
