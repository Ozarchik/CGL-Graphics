#ifndef CGL_NODE_H
#define CGL_NODE_H

#include <vector>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/graphics/shader.h>
#include <cgl/core/transform.h>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/core/camera.h>
#include <cgl/graphics/material/material.h>

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

    void addChild(CGL::Node* node);
    std::vector<CGL::Node*> childs() const;
    void addMesh(CGL::Mesh* mesh);
    void addMesh(CGL::Mesh* mesh, const Material &material);
    void setTransform(const CGL::Transform& transform);
    void setPrimitiveType(GLenum type);

    CGL::BoundingBox boundingBox() const;
    void update(CGL::Camera& camera, const CGL::Transform& parentTransform = {});

private:
    Node* m_parent = nullptr;
    std::vector<MeshRenderer> m_renders;
    std::vector<Node*> m_childs;
    CGL::Shader& m_shader; // it's tmp solve, need to change to shader_ptr
    CGL::Transform m_transform;
};
};

#endif
