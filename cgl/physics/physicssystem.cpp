#include <cgl/physics/physicssystem.h>
#include <cgl/core/event/inputcontroller.h>
#include <cgl/core/engine.h>

cgl::PhysicsSystem::PhysicsSystem()
{
    cglInputController().addSubscriber(&m_raycast);
}

void cgl::PhysicsSystem::update()
{
    // TODO: implement
    m_raycast.draw();
}
