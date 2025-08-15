#ifndef CGL_COMMAND_H
#define CGL_COMMAND_H

#include <cgl/graphics/scene/scene.h>

namespace CGL {
class ICommand {
public:
    virtual ~ICommand() {};

    virtual void execute(CGL::Scene& scene) = 0;

private:

};
}

#endif
