#ifndef CGL_NODE_H
#define CGL_NODE_H

#include <vector>
// #include <memory>
#include <cgl/mesh/common/mesh.h>
#include <cgl/shader.h>
#include <cgl/transform.h>
#include <cgl/mesh/common/mesh.h>
#include <cgl/camera.h>
#include <cgl/material.h>

namespace CGL {
struct MeshRenderer {
    MeshRenderer(Mesh* mesh) {
        m_mesh = mesh;
    }
    MeshRenderer(Mesh* mesh, Material material) {
        m_mesh = mesh;
        m_material = material;
    }

    Mesh* m_mesh;
    Material m_material;
};

class Node {
public:
    Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform = {});
    Node(std::vector<CGL::Mesh*> mesh, CGL::Shader& shader, CGL::Transform transform = {});
    Node(CGL::Shader &shader, CGL::Transform transform = {});

    ~Node();

    bool selected() const;
    void setSelected(bool state);
    void addChild(CGL::Node* node);
    void addMesh(CGL::Mesh* mesh, const Material &material);
    void setTransform(const CGL::Transform& transform);
    void setPrimitiveType(GLenum type);
    void update(CGL::Camera& camera, const CGL::Transform& parentTransform = {});

private:
    Node* m_parent = nullptr;
    std::vector<MeshRenderer> m_renders;
    std::vector<Node*> m_childs;
    CGL::Shader& m_shader; // it's tmp solve, need to change to shader_ptr
    CGL::Transform m_transform;
    bool m_selected;
};
};

#endif
