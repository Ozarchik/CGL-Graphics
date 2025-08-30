#ifndef CGL_NODE_H
#define CGL_NODE_H

#include <vector>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/graphics/shader.h>
#include <cgl/core/transform.h>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/core/camera.h>
#include <cgl/graphics/material/material.h>
#include <memory>

namespace CGL {
struct MeshRenderer {
    MeshRenderer() = default;

    MeshRenderer(std::shared_ptr<Mesh> mesh) {
        m_mesh = mesh;
    }
    MeshRenderer(std::shared_ptr<Mesh> mesh, Material material) {
        m_mesh = mesh;
        m_material = {material};
    }

    std::shared_ptr<Mesh> m_mesh;
    std::vector<Material> m_material;
};



class Node {
public:
    Node(std::shared_ptr<Mesh> mesh, std::shared_ptr<CGL::Shader> shader, CGL::Transform transform = {});
    Node(std::vector<std::shared_ptr<Mesh>> mesh, std::shared_ptr<CGL::Shader> shader, CGL::Transform transform = {});
    Node(std::shared_ptr<Shader> shader, CGL::Transform transform = {});

    ~Node();

    void addChild(CGL::Node* node);
    std::vector<CGL::Node*> childs() const;
    void addMesh(std::shared_ptr<Mesh> mesh);
    void addMesh(std::shared_ptr<Mesh> mesh, const Material &material);
    void setTransform(const CGL::Transform& transform);
    Transform transform() const;
    Transform& transformRef();
    void setPrimitiveType(RenderContext::Primitive type);

    CGL::BoundingBox boundingBox() const;
    void update(CGL::Camera& camera, const CGL::Transform& parentTransform = {});

private:
    MeshRenderer m_renderer;
    std::vector<Node*> m_childs;
    std::shared_ptr<CGL::Shader> m_shader;
    CGL::Transform m_transform;
};
};

#endif
