#pragma once
#include <vector>
#include "mesh.h"
#include "shaderprogram.h"

namespace CGL {
class Scene {
public:
    void render(ShaderProgram& shaderProgram);
    void addMesh(Mesh* mesh);
    void clear();
    
private:
    std::vector<Mesh*> m_meshes;
};
};