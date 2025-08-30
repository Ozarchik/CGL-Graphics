#include <cgl/physics/raycast.h>
#include <cgl/core/engine.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>

cgl::Raycast::Raycast(cgl::Scene& scene)
    : m_scene(scene)
{

}

// Reference: https://antongerdelan.net/opengl/raycasting.html
void cgl::Raycast::seek(float mouseX, float mouseY)
{
    glm::vec4 ray_ndc;
    ray_ndc.x = (2.0f * mouseX) / (cgl::CoreContext::instance().width()) - 1.0f;
    ray_ndc.y = 1.0f - (2.0f * mouseY) / cgl::CoreContext::instance().height();
    ray_ndc.z = -1.0f;
    ray_ndc.w = 1.0f;

    // 3. Get camera coords
    // eye = inverse(projection) * ray_ndc
    // eye = vec4(eye.xy, -1.0, 0.0)
    glm::vec4 eye = glm::inverse(cglEngine().activeCamera()->getProjection().data()) * ray_ndc;
    eye = glm::vec4(eye.x, eye.y, -1.0f, 0.0f);


    // 4. Get world coords
    // world = (inverse(view) * eye).xyz
    // world = normalize(world)
    glm::vec3 direction = glm::inverse(cglEngine().activeCamera()->getView().data()) * eye; // vec4 -> vec3 check conversion
    direction = glm::normalize(direction);
    glm::vec3 origin = cglEngine().activeCamera()->pos();


    m_raylines.push_back(*cglEngine().activeCamera());
    m_raylines.back().update(origin, direction);

    for (auto& node: m_scene.nodes()) {

        float t;
        cgl::BoundingBox box = node->boundingBox();

        static int count = 0;
        if (intersectRayAABB(origin, direction, box, t)) {
            m_scene.setSelectedNode(node.get());
            break;
        }
    }

    std::cout << std::endl;
}

void cgl::Raycast::draw()
{
    for (auto& rl: m_raylines) {
        rl.draw();
    }
}

bool cgl::Raycast::intersectRayAABB(glm::vec3 origin, glm::vec3 direction, cgl::BoundingBox& box, float& tMin)
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

void cgl::Raycast::mouseEventHandler(const MouseEvent &event)
{
    if (event.type() == cgl::Mouse_Release) {
        GLint data[4];
        glGetIntegerv(GL_VIEWPORT, data);
        int w, h;
        glfwGetWindowSize(cgl::CoreContext::instance().handler(), &w, &h);
        std::cout << "window: (" << w << ", " << h << ")" << std::endl;
        std::cout << "viewport: (" << data[0] << ", " << data[1] << ") (" << data[2] << ", " << data[3] << ")" << std::endl;
        std::cout << "mouse pos: (" << event.x() << ", " << event.y() << ")" << std::endl;
        std::cout << std::endl;
    // m_lastX = event.x();
    // m_lastY = event.y();
        seek(event.x(), event.y());
    }

    // if (event.type() == cgl::MouseAction::Release)
        // m_scene.upselectNode();
}

void cgl::Raycast::keyEventHandler(const KeyEvent &event)
{
    // seek(m_lastX, m_lastY);
}
