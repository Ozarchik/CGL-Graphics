#pragma once

#include "mesh.h"

namespace CGL {
class Cube: public Mesh {
public:
    Cube();
    Cube(const glm::vec3& pos);
    Cube(const glm::vec3& pos, const std::vector<TextureBase>& textures);
    Cube(const std::vector<Vertex>& vertices, const std::vector<TextureBase>& textures, const std::vector<unsigned int>& indices);
    ~Cube();

    void draw(Shader& Shader);

private:
    float m_sizeX = 0.5f, m_sizeY = 0.5f, m_sizeZ = 0.5f;

    std::vector<float> texes {
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
        1.0f,  0.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
        1.0f,  0.0f,
        1.0f,  0.0f,
        0.0f,  0.0f,
        0.0f,  1.0f
    };

    std::vector<float> normals {
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };

    std::vector<float> colors {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    };

    std::vector<float> vectices {
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,

         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,

         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,

          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,

         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x, -m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,

         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
          m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y,  m_sizeZ + m_pos.z,
         -m_sizeX + m_pos.x,  m_sizeY + m_pos.y, -m_sizeZ + m_pos.z,
    };
};
}
