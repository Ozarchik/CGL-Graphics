#pragma once

#include "mesh.h"

namespace CGL {
class Cube: public Mesh {
public:
    Cube(const glm::vec3& position);
    Cube(const glm::vec3& position, const std::vector<TextureBase>& textures);
    Cube(const std::vector<Vertex>& vertices, const std::vector<TextureBase>& textures, const std::vector<unsigned int>& indices);
    ~Cube();

    void draw(Shader& Shader);

private:
    float m_sizeX = 0.5f, m_sizeY = 0.5f, m_sizeZ = 0.5f;
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;

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
         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,

         -m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,

         -m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,

          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,

         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x, -m_sizeY + m_y, -m_sizeZ + m_z,

         -m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
          m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y,  m_sizeZ + m_z,
         -m_sizeX + m_x,  m_sizeY + m_y, -m_sizeZ + m_z,
    };
};
}
