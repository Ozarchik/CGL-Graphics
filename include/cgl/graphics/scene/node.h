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

namespace cgl {
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
    Node(std::shared_ptr<Mesh> mesh, std::shared_ptr<cgl::Shader> shader, cgl::Transform transform = {});
    Node(std::vector<std::shared_ptr<Mesh>> mesh, std::shared_ptr<cgl::Shader> shader, cgl::Transform transform = {});
    Node(std::shared_ptr<Shader> shader, cgl::Transform transform = {});

    ~Node();

    void addChild(cgl::Node* node);
    std::vector<cgl::Node*> childs() const;
    void addMesh(std::shared_ptr<Mesh> mesh);
    void addMesh(std::shared_ptr<Mesh> mesh, const Material &material);
    void setTransform(const cgl::Transform& transform);
    Transform transform() const;
    Transform& transformRef();
    void setPrimitiveType(cgl::Primitive type);

    cgl::BoundingBox boundingBox() const;
    void update(cgl::Camera& camera, const cgl::Transform& parentTransform = {});

private:
    MeshRenderer m_renderer;
    std::vector<Node*> m_childs;
    std::shared_ptr<cgl::Shader> m_shader;
    cgl::Transform m_transform;
};
};

#endif
