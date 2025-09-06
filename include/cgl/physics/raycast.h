#ifndef CGL_RAYCAST_H
#define CGL_RAYCAST_H

#include <cgl/core/camera.h>
#include <cgl/core/corecontext.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/physics/rayline.h>

namespace cgl {
class Raycast: public cgl::Object {
public:

    void seek(float mouseX, float mouseY);
    void draw();

protected:
    void mouseEventHandler(const cgl::MouseEvent& event) override;
    void keyEventHandler(const cgl::KeyEvent& event) override;

private:
    bool intersectRayAABB(glm::vec3 origin, glm::vec3 direction, BoundingBox &box, float &tMin);

private:
    std::vector<cgl::RayLine> m_raylines;
};
}

#endif
