#ifndef CGL_MOVECOMMAND_H
#define CGL_MOVECOMMAND_H

#include <cgl/core/command/icommand.h>


namespace cgl {
class MoveCommand: public cgl::ICommand
{
public:
    MoveCommand(float x, float y, float z);

    void execute(cgl::Scene& scene) override;

private:
    float m_x, m_y, m_z;
};
}

#endif // CGL_MOVECOMMAND_H
