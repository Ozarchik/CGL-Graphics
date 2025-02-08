#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "texture.h"
#include "texturebase.h" 
#include "vertex.h"
#include "meshbuffer.h"

#include "stb_image.h"

namespace CGL {
class Mesh {
public:
    explicit Mesh();
    explicit Mesh(const std::vector<Vertex>& vertices);
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> &indices);
    explicit Mesh(const std::vector<Vertex>& vertices, const TextureBase& texture);
    explicit Mesh(const std::vector<Vertex>& vertices, const TextureBase& texture, const std::vector<unsigned int> &indices);
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures);
    explicit Mesh(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures, const std::vector<unsigned int>& indices);

    virtual void setup();
    virtual void draw(Shader& Shader);
    virtual void addTexture(const std::vector<CGL::TextureBase>& textures);

    void setPrimitiveType(GLenum type);

protected:
    CGL::MeshBuffer m_buffer;
    GLenum m_primitiveType = GL_TRIANGLES;
};
}
