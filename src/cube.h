#pragma once

#include "mesh.h"

namespace CGL {
class Cube: public Mesh {
public:
    Cube(const unsigned int& size = 1.0);
    Cube(const CGL::TextureBase& texture, const unsigned int& size = 1.0);
    Cube(const glm::vec3& pos, const unsigned int& size = 1.0);
    Cube(const glm::vec3& pos, const CGL::TextureBase& texture, const unsigned int& size = 1.0);
    Cube(const glm::vec3& pos, const std::vector<CGL::TextureBase>& textures, const unsigned int& size = 1.0);
    Cube(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures, const std::vector<unsigned int>& indices);
    ~Cube();

    void draw(Shader& Shader);

private:
    float m_size = 1.0f;
};
}
