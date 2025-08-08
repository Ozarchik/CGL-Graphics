#include <cgl/physics/raycast.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

glm::vec3 dir;
glm::vec3 org;

CGL::Raycast::Raycast(CGL::Context &context, CGL::Scene& scene, CGL::Camera& camera)
    : m_context(context), m_scene(scene), m_camera(camera), m_rayline(m_camera)
{

}

// Reference: https://antongerdelan.net/opengl/raycasting.html
void CGL::Raycast::seek(float mouseX, float mouseY)
{
    // 1. Get 3D normalized coords
    // x: (2.0 * mouseX)/width - 1.0
    // y: 1.0 - (2.0 * mouseY)/height
    // z: 1
    // ray_3nd = (x,y,z)
    glm::vec3 ray_3nd;
    ray_3nd.x = (2.0f * mouseX) / (m_context.width()) - 1.0f;
    ray_3nd.y = 1.0f - (2.0f * mouseY) / m_context.height();
    ray_3nd.z = 1.0f;


    // 2. Get 4D Homogenius coords
    // hom_coords = ([-1;1], [-1;1], [-1;1], [-1;1])
    // clip = vec4(ray_3nd.xy, -1.0, 1.0);
    glm::vec4 clip = glm::vec4(ray_3nd.x, ray_3nd.y, -1.0f, 1.0f);


    // 3. Get camera coords
    // eye = inverse(projection) * clip
    // eye = vec4(eye.xy, -1.0, 0.0)
    glm::vec4 eye = glm::inverse(m_camera.getProjection().data()) * clip;
    eye = glm::vec4(eye.x, eye.y, -1.0f, 0.0f);


    // 4. Get world coords
    // world = (inverse(view) * eye).xyz
    // world = normalize(world)
    glm::vec3 world = glm::inverse(m_camera.getView().data()) * eye; // vec4 -> vec3 check conversion
    world = glm::normalize(world);

    glm::vec3 origin = m_camera.pos();
    glm::vec3 direction = world;

    // glm::vec3 direction = /*world*/ glm::vec3(0.0, 0.0, 20.0f);
    // glm::vec3 origin = m_camera.pos();

    // glm::mat4 view = m_camera.getView().data();
    // glm::vec3 camPosition = glm::vec3(glm::inverse(view)[3]);
    // org = camPosition;
    // org = glm::vec3(0.0);
    // glm::vec3 cameraPos = m_camera.pos();
    // glm::vec3 cameraDir = m_camera.front();
    // glm::vec3 lookAtPoint = cameraPos + cameraDir;
    org = origin;//lookAtPoint;
    dir = direction;

    glm::vec4 viewport(0, 0, m_context.width(), m_context.height());
    glm::vec3 rayStart = glm::unProject(glm::vec3(mouseX, m_context.height() - mouseY, 0.0f),
                                        m_camera.getView().data(), m_camera.getProjection().data(), viewport);
    glm::vec3 rayEnd   = glm::unProject(glm::vec3(mouseX, m_context.height() - mouseY, 1.0f),
                                      m_camera.getView().data(), m_camera.getProjection().data(), viewport);
    glm::vec3 rayDir   = glm::normalize(rayEnd - rayStart);

    origin = org;
    int index = 0;
    // m_rayline.update(origin, direction);
    // m_rayLine.set
    // org = rayEnd;


    m_raylines.push_back(m_camera);
    m_raylines.back().update(origin, direction);

    for (auto& node: m_scene.nodes()) {

        float t;
        CGL::BoundingBox box = node->boundingBox();

        static int count = 0;
        node->setSelected(false);
        if (intersectRayAABB(origin, direction, box, t)) {
            m_scene.setSelectedNode(node);
            node->setSelected(true);
            break;
        }
    }

    std::cout << std::endl;
}

void CGL::Raycast::draw()
{
    for (auto& rl: m_raylines) {
        rl.draw();
    }
}

bool CGL::Raycast::intersectRayAABB(glm::vec3 origin, glm::vec3 direction, CGL::BoundingBox& box, float& tMin)
{
    float t1 = (box.min.x - origin.x) / direction.x;
    float t2 = (box.max.x - origin.x) / direction.x;
    float t3 = (box.min.y - origin.y) / direction.y;
    float t4 = (box.max.y - origin.y) / direction.y;
    float t5 = (box.min.z - origin.z) / direction.z;
    float t6 = (box.max.z - origin.z) / direction.z;

    float tmin1 = std::min(t1, t2);
    float tmin2 = std::min(t3, t4);
    float tmin3 = std::min(t5, t6);

    float tmax1 = std::max(t1, t2);
    float tmax2 = std::max(t3, t4);
    float tmax3 = std::max(t5, t6);


    float tmin = std::max(std::max(tmin1, tmin2), tmin3);
    float tmax = std::min(std::min(tmax1, tmax2), tmax3);

    if (tmax < 0 || tmin > tmax)
        return false;

    tMin = tmin;
    return true;
}

static double m_lastX;
static double m_lastY;

void CGL::Raycast::mouseEventHandler(const MouseEvent &event)
{
    // if (event.type() == CGL::MouseType::Press)
    m_lastX = event.x();
    m_lastY = event.y();
    seek(event.x(), event.y());
}

void CGL::Raycast::keyEventHandler(const KeyEvent &event)
{
    // seek(m_lastX, m_lastY);
}
