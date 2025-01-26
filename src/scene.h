#pragma once
#include <vector>
#include "mesh.h"
#include "shader.h"

namespace CGL {
class Scene {
public:
    void render(Shader& Shader);
    void addMesh(Mesh* mesh);
    void clear();
    
private:
    std::vector<Mesh*> m_meshes;
};
};