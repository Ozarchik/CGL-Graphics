#pragma once
#include <vector>
#include <cgl/mesh/common/mesh.h>
#include <cgl/shader.h>

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
