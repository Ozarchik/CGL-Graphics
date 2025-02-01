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
         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,

         -m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,

         -m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,

          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,

         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x, -m_size + m_pos.y, -m_size + m_pos.z,

         -m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
          m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y,  m_size + m_pos.z,
         -m_size + m_pos.x,  m_size + m_pos.y, -m_size + m_pos.z,
    };

    std::vector<CGL::Vertex> vertices = {

        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },

        { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },

        { {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },

        { { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },

        { {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },

        { {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, {-0.5f,  0.5f, -0.5f} },
        { {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {-0.5f,  0.5f, -0.5f} }
    };

};
}
