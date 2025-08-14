#include <cgl/node.h>
#include <limits>

CGL::Node::Node(CGL::Mesh* mesh, CGL::Shader& shader, CGL::Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    m_renders.push_back(CGL::MeshRenderer{mesh});
}

CGL::Node::Node(std::vector<Mesh *> meshes, Shader &shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    for (int i = 0; i < meshes.size(); i++) {
        m_renders.push_back(CGL::MeshRenderer{meshes[i]});
    }
}

CGL::Node::Node(Shader &shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{

}

CGL::Node::~Node()
{
    for (auto& render: m_renders) {
        delete render.m_mesh;
    }
}

bool CGL::Node::selected() const
{
    return m_selected;
}

void CGL::Node::setSelected(bool state)
{
    m_selected = state;
}

void CGL::Node::addChild(Node *node)
{
    m_childs.push_back(node);
}

std::vector<CGL::Node *> CGL::Node::childs() const
{
    return m_childs;
}

void CGL::Node::addMesh(Mesh *mesh)
{
    if (!mesh)
        return;

    m_renders.emplace_back(mesh);
}

void CGL::Node::addMesh(Mesh *mesh, const Material &material)
{
    if (!mesh)
        return;
    
    m_renders.emplace_back(mesh, material);
}

void CGL::Node::setTransform(const CGL::Transform& transform)
{
    m_transform = transform;
}

void CGL::Node::setPrimitiveType(GLenum type)
{
    for (auto& render: m_renders) {
        render.m_mesh->setPrimitiveType(type);
    }
}

CGL::BoundingBox CGL::Node::boundingBox() const
{
    CGL::BoundingBox totalBox;
    totalBox.min = glm::vec3(std::numeric_limits<float>::max());
    totalBox.max = glm::vec3(std::numeric_limits<float>::lowest());

    glm::mat4 modelMatrix = m_transform.data();

    for (auto& render: m_renders) {
        BoundingBox localBox = render.m_mesh->boundingBox();

        glm::vec3 corners[8] = {
            {localBox.min.x, localBox.min.y, localBox.min.z},
            {localBox.max.x, localBox.min.y, localBox.min.z},
            {localBox.min.x, localBox.max.y, localBox.min.z},
            {localBox.max.x, localBox.max.y, localBox.min.z},
            {localBox.min.x, localBox.min.y, localBox.max.z},
            {localBox.max.x, localBox.min.y, localBox.max.z},
            {localBox.min.x, localBox.max.y, localBox.max.z},
            {localBox.max.x, localBox.max.y, localBox.max.z},
        };

        for (const auto& corner : corners) {
            glm::vec3 transformed = glm::vec3(modelMatrix * glm::vec4(corner, 1.0f));
            totalBox.min = glm::min(totalBox.min, transformed);
            totalBox.max = glm::max(totalBox.max, transformed);
        }
    }

    return totalBox;
}

void CGL::Node::update(CGL::Camera& camera, const Transform &parentTransform)
{
    CGL::Transform resultTransform = parentTransform * m_transform;

    m_shader.use();
    m_shader.setMat4("model", resultTransform);
    m_shader.setMat4("view", camera.getView());
    m_shader.setMat4("projection", camera.getProjection());
    m_shader.setBool("selected", m_selected);

    for (auto& render: m_renders) {
        render.m_material.draw(m_shader);
        render.m_mesh->draw(m_shader);        
    }

    for (const auto child: m_childs) {
        child->update(camera, resultTransform);
    }
}
