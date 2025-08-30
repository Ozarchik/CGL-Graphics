#include <cgl/graphics/scene/node.h>
#include <limits>

cgl::Node::Node(std::shared_ptr<cgl::Mesh> mesh, std::shared_ptr<cgl::Shader> shader, cgl::Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    m_renderer.m_mesh = mesh;
}

cgl::Node::Node(std::vector<std::shared_ptr<Mesh>> meshes, std::shared_ptr<cgl::Shader> shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
    for (int i = 0; i < meshes.size(); i++) {
        m_renderer.m_mesh = meshes[i];
    }
}

cgl::Node::Node(std::shared_ptr<cgl::Shader> shader, Transform transform)
    : m_shader(shader)
    , m_transform(transform)
{
}

cgl::Node::~Node()
{
}

void cgl::Node::addChild(Node *node)
{
    m_childs.push_back(node);
}

std::vector<cgl::Node *> cgl::Node::childs() const
{
    return m_childs;
}

void cgl::Node::addMesh(std::shared_ptr<Mesh> mesh)
{
    if (!mesh)
        return;

    m_renderer = MeshRenderer(mesh);
}

void cgl::Node::addMesh(std::shared_ptr<Mesh> mesh, const Material &material)
{
    if (!mesh)
        return;
    
    m_renderer = MeshRenderer(mesh, material);
}

void cgl::Node::setTransform(const cgl::Transform& transform)
{
    m_transform = transform;
}

cgl::Transform &cgl::Node::transformRef()
{
    return m_transform;
}

cgl::Transform cgl::Node::transform() const
{
    return m_transform;
}

void cgl::Node::setPrimitiveType(cgl::Primitive type)
{
    if (m_renderer.m_mesh)
        m_renderer.m_mesh->setPrimitiveType(type);
}

cgl::BoundingBox cgl::Node::boundingBox() const
{
    cgl::BoundingBox totalBox;
    totalBox.min = glm::vec3(std::numeric_limits<float>::max());
    totalBox.max = glm::vec3(std::numeric_limits<float>::lowest());

    glm::mat4 modelMatrix = m_transform.data();


    BoundingBox localBox = m_renderer.m_mesh->boundingBox();

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

    return totalBox;
}

void cgl::Node::update(cgl::Camera& camera, const Transform &parentTransform)
{
    cgl::Transform resultTransform = parentTransform * m_transform;

    m_shader->use();
    m_shader->setModel(resultTransform);
    m_shader->setView(camera.getView());
    m_shader->setProjection(camera.getProjection());
    cglErrors();
    for (auto& m: m_renderer.m_material)
        m.draw(*m_shader);
    cglErrors();
    m_renderer.m_mesh->draw(*m_shader);
    for (const auto child: m_childs) {
        child->update(camera, resultTransform);
    }
}
