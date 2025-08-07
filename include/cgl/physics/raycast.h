#ifndef CGL_RAYCAST_H
#define CGL_RAYCAST_H

#include <cgl/camera.h>
#include <cgl/context.h>

namespace CGL {
class Raycast: public CGL::Object {
public:
    Raycast(CGL::Context& context);

    void seek(CGL::Camera& camera, float mouseX, float mouseY);

protected:
    void mouseEventHandler(const CGL::MouseEvent& event) override;

private:
    CGL::Context& m_context;
};
}

#endif
