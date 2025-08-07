#include <cgl/physics/raycast.h>
#include <glm/glm.hpp>
#include <iostream>

CGL::Raycast::Raycast(Context &context)
    : m_context(context)
{

}

// Reference: https://antongerdelan.net/opengl/raycasting.html
void CGL::Raycast::seek(CGL::Camera &camera, float mouseX, float mouseY)
{
    // 1. Get 3D normalized coords
    // x: (2.0 * mouseX)/width - 1.0
    // y: 1.0 - (2.0 * mouseY)/height
    // z: 1
    // ray_3nd = (x,y,z)

    glm::vec3 ray_3nd;
    ray_3nd.x = (2.0f * mouseX) / m_context.width() - 1.0f;
    ray_3nd.y = 1.0f - (2.0f * mouseY) / m_context.height();
    ray_3nd.z = 1.0f;

    // 2. Get 4D Homogenius coords
    // hom_coords = ([-1;1], [-1;1], [-1;1], [-1;1])
    // clip = vec4(ray_3nd.xy, -1.0, 1.0);
    glm::vec4 clip = glm::vec4(ray_3nd.x, ray_3nd.y, -1.0f, 1.0f);


    // 3. Get camera coords
    // eye = inverse(projection) * clip
    // eye = vec4(eye.xy, -1.0, 0.0)

    glm::vec4 eye = glm::inverse(camera.getProjection().data()) * clip;
    eye = glm::vec4(eye.x, eye.y, -1.0f, 0.0f);

    // 4. Get world coords
    // world = (inverse(view) * eye).xyz
    // world = normalize(world)

    glm::vec3 world = glm::inverse(camera.getView().data()) * eye; // vec4 -> vec3 check conversion
    world = glm::normalize(world);
}

void CGL::Raycast::mouseEventHandler(const MouseEvent &event)
{
}
