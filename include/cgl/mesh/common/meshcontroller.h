#ifndef MESHCONTROLLER_H
#define MESHCONTROLLER_H

#include <cgl/mesh/common/meshglobals.h>
#include <cgl/shader.h>

namespace CGL {
class Mesh;
class MeshController {
public:
    MeshController() = default;
    // MeshController(CGL::Mesh& mesh);
    void setRenderMode(CGL::Shader& shader, CGL::ColorRenderMode mode);

private:
    CGL::Mesh* m_mesh;
};
}

#endif