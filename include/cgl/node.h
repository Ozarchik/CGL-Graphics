#ifndef CGL_NODE_H
#define CGL_NODE_H

#include <vector>
// #include <memory>
#include <cgl/mesh/common/mesh.h>
#include <cgl/shader.h>
#include <cgl/transform.h>
#include <cgl/mesh/common/mesh.h>

namespace CGL {
class Node {
public:
    Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform = {});
    ~Node();
    void setTransform(const CGL::Transform& transform);
    void setPrimitiveType(GLenum type);
    void update();    

private:
    Node* m_parent = nullptr;
    Mesh* m_mesh = nullptr;
    std::vector<Node*> m_childs;
    CGL::Shader& m_shader; // it's tmp solve, need to change to shader_ptr
    CGL::Transform m_transform;
};
};

#endif
