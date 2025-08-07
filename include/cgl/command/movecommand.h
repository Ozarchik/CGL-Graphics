#ifndef CGL_MOVECOMMAND_H
#define CGL_MOVECOMMAND_H

#include <cgl/command/icommand.h>


namespace CGL {
class MoveCommand: public CGL::ICommand
{
public:

    MoveCommand(float x, float y, float z);

    void execute(CGL::Scene& scene) override;

private:
    float m_x, m_y, m_z;
};
}

#endif // CGL_MOVECOMMAND_H
