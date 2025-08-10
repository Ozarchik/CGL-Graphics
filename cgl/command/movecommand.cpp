#include <cgl/command/movecommand.h>
#include <iostream>

CGL::MoveCommand::MoveCommand(float x, float y, float z)
    : m_x(x), m_y(y), m_z(z)
{}

void CGL::MoveCommand::execute(CGL::Scene& scene)
{
    CGL::Transform moveTransform;
    moveTransform.translate(m_x, m_y, m_z);

    if (scene.selectedNode())
        scene.selectedNode()->setTransform(moveTransform);
}
