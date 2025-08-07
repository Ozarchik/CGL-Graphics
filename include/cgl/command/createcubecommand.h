#ifndef CGL_CREATECUBECOMMAND_H
#define CGL_CREATECUBECOMMAND_H

#include <cgl/command/icommand.h>

namespace CGL {
class CreateCubeCommand: public ICommand
{
public:
    CreateCubeCommand();

    void execute(CGL::Scene& scene) override;
};
}

#endif // CGL_CREATECUBECOMMAND_H
