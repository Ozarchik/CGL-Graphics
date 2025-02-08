#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "model.h"
#include "shader.h"

namespace CGL {
class SolarSystem
{
public:
    SolarSystem();
    void use(
        CGL::SolarSystem
    );

private:
    CGL::Model objects[8];
};
}

#endif // SOLARSYSTEM_H
