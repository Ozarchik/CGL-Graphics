#ifndef GEOMETRYEXAMPLE_H
#define GEOMETRYEXAMPLE_H

#include <cgl/shader.h>
#include <cgl/scene.h>
#include <cgl/camera.h>
#include <cgl/window.h>

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
