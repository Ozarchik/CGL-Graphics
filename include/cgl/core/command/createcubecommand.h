#ifndef CGL_CREATECUBECOMMAND_H
#define CGL_CREATECUBECOMMAND_H

#include <cgl/core/command/icommand.h>

namespace cgl {
class CreateCubeCommand: public ICommand
{
public:
    CreateCubeCommand();

    void execute(cgl::Scene& scene) override;
};
}

#endif // CGL_CREATECUBECOMMAND_H
