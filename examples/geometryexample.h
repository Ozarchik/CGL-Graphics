#ifndef GEOMETRYEXAMPLE_H
#define GEOMETRYEXAMPLE_H

#include "shader.h"
#include "scene.h"
#include "camera.h"
#include "window.h"

namespace CGL {
class GeometryExample
{
public:
    GeometryExample();
    void use(const CGL::Window& window, const CGL::Camera& camera);

protected:
    CGL::Scene m_scene;
    CGL::Shader m_shader;
};
}

#endif // GEOMETRYEXAMPLE_H
