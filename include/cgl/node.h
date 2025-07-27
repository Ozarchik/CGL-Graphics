#ifndef CGL_NODE_H
#define CGL_NODE_H

#include <vector>
#include <cgl/mesh/common/mesh.h>
#include <cgl/shader.h>
#include <cgl/mesh/common/mesh.h>

namespace CGL {
class Node {
public:
    Node() = default;
    void update(CGL::Shader& shader);    
    void addMesh(CGL::Mesh* mesh);

private:
    Node* parent = nullptr;
    std::vector<Mesh*> m_meshes;
    std::vector<Node*> m_childs;
};
};

#endif