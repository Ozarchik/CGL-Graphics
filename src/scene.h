#pragma once
#include <vector>
#include "mesh.h"
#include "shader.h"

namespace CGL {
class Scene {
public:
    Scene() = default;
    ~Scene();
    void render(Shader& Shader);
    void addMesh(Mesh* mesh);
    void clear();
    std::vector<Mesh*> meshes() const;
    
private:
    std::vector<Mesh*> m_meshes;
};
}
