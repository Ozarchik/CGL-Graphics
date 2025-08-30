#include <cgl/core/command/movecommand.h>
#include <iostream>

cgl::MoveCommand::MoveCommand(float x, float y, float z)
    : m_x(x), m_y(y), m_z(z)
{}

void cgl::MoveCommand::execute(cgl::Scene& scene)
{
    cgl::Transform moveTransform;
    moveTransform.translate(m_x, m_y, m_z);

    if (scene.selectedNode().has_value())
        scene.selectedNode().value()->setTransform(moveTransform);
}
