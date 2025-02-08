#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <vector>
#include "vertex.h"
#include "texturebase.h"

namespace CGL {
struct MeshBuffer
{
public:
    MeshBuffer() = default;
    MeshBuffer(const std::vector<Vertex>& vertices);
    MeshBuffer(const std::vector<Vertex>& vertices, const TextureBase& texture);
    MeshBuffer(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures);
    MeshBuffer(const std::vector<Vertex>& vertices, const std::vector<CGL::TextureBase>& textures, const std::vector<unsigned int>& indices);

    void setTextures(const std::vector<TextureBase>& newTextures);

    void bind();
    void unbind();

private:
    void setup();

public:
    std::vector<CGL::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<CGL::TextureBase> textures;

    unsigned int vao, vbo, ebo;
};
}

#endif // MESHBUFFER_H
