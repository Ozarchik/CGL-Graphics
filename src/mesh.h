#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "texturebase.h" 
#include "vertex.h"

#include "stb_image.h"

namespace CGL {
class Mesh {
public:
    Mesh() = default;
    Mesh(const glm::vec3& pos);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<TextureBase>& textures, const std::vector<unsigned int>& indices);

    virtual void setup();
    virtual void draw(Shader& Shader);

    virtual void addTexture(const std::vector<TextureBase>& textures);

protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<TextureBase> m_textures;

    glm::vec3 m_pos;
    unsigned int VAO, VBO, EBO;
    CGL::Buffer<float> m_coordBuffer;
    CGL::Buffer<float> m_normalBuffer;
    CGL::Buffer<float> m_colorBuffer;
    CGL::Buffer<float> m_texBuffer;
};
}
