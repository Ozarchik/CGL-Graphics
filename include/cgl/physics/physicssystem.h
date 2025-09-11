#ifndef CGL_PHYSICSSYSTEM_H
#define CGL_PHYSICSSYSTEM_H

#include <cgl/graphics/scene/scene.h>
#include <cgl/physics/raycast.h>

namespace cgl {

class PhysicsSystem
{
public:
    PhysicsSystem();
    void update();

private:
    Raycast m_raycast;
};

}

#endif // CGL_PHYSICSSYSTEM_H
