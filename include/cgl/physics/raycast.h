#ifndef CGL_RAYCAST_H
#define CGL_RAYCAST_H

#include <cgl/core/camera.h>
#include <cgl/core/corecontext.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/physics/rayline.h>

namespace CGL {
class Raycast: public CGL::Object {
public:
    Raycast(CGL::CoreContext& context, CGL::Scene& scene, CGL::Camera& camera);

    void seek(float mouseX, float mouseY);
    void draw();

protected:
    void mouseEventHandler(const CGL::MouseEvent& event) override;
    void keyEventHandler(const CGL::KeyEvent& event) override;

private:
    bool intersectRayAABB(glm::vec3 origin, glm::vec3 direction, BoundingBox &box, float &tMin);

private:
    CGL::CoreContext& m_context;
    CGL::Scene& m_scene;
    CGL::Camera& m_camera;
    std::vector<CGL::RayLine> m_raylines;
};
}

#endif
