#include <cgl/physics/raycast.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

CGL::Raycast::Raycast(CGL::CoreContext &context, CGL::Scene& scene, CGL::Camera& camera)
    : m_context(context), m_scene(scene), m_camera(camera)//, m_rayline(m_camera)
{

}

// Reference: https://antongerdelan.net/opengl/raycasting.html
void CGL::Raycast::seek(float mouseX, float mouseY)
{
    glm::vec4 ray_ndc;
    ray_ndc.x = (2.0f * mouseX) / (m_context.width()) - 1.0f;
    ray_ndc.y = 1.0f - (2.0f * mouseY) / m_context.height();
    ray_ndc.z = -1.0f;
    ray_ndc.w = 1.0f;

    // 3. Get camera coords
    // eye = inverse(projection) * ray_ndc
    // eye = vec4(eye.xy, -1.0, 0.0)
    glm::vec4 eye = glm::inverse(m_camera.getProjection().data()) * ray_ndc;
    eye = glm::vec4(eye.x, eye.y, -1.0f, 0.0f);


    // 4. Get world coords
    // world = (inverse(view) * eye).xyz
    // world = normalize(world)
    glm::vec3 direction = glm::inverse(m_camera.getView().data()) * eye; // vec4 -> vec3 check conversion
    direction = glm::normalize(direction);
    glm::vec3 origin = m_camera.pos();


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
    if (event.type() == CGL::Mouse_Release) {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);
        int w, h;
        glfwGetWindowSize(m_context.handler(), &w, &h);
        std::cout << "window: (" << w << ", " << h << ")" << std::endl;
        std::cout << "viewport: (" << data[0] << ", " << data[1] << ") (" << data[2] << ", " << data[3] << ")" << std::endl;
        std::cout << "mouse pos: (" << event.x() << ", " << event.y() << ")" << std::endl;
        std::cout << std::endl;
    // m_lastX = event.x();
    // m_lastY = event.y();
        seek(event.x(), event.y());
    }

    // if (event.type() == CGL::MouseAction::Release)
        // m_scene.upselectNode();
}

void CGL::Raycast::keyEventHandler(const KeyEvent &event)
{
    // seek(m_lastX, m_lastY);
}
