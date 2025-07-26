#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <cgl/scene.h>
#include <cgl/shader.h>
#include <cgl/window.h>
#include <cgl/camera.h>

struct PlanetInfo {
    float distance;
    float radius;
    float localPeriod;
    float yearPeriod;
    float moonDistance;
    float moonPeriod;
};

namespace CGL {
class SolarSystem
{
public:
    SolarSystem();
    void use(Transform &model, Transform &view, Transform &projection);

private:
    CGL::Scene m_scene;
    CGL::Shader m_shader;

    std::vector<PlanetInfo> m_info;
};
}

#endif // SOLARSYSTEM_H
