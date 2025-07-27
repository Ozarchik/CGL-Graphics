#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <vector>
#include <cgl/vertex.h>
#include <cgl/texture/texturebase.h>

namespace CGL {
struct MeshBuffer
{
public:
    MeshBuffer(
        const std::vector<Vertex>& vertices,
        const std::vector<CGL::TextureBase>& textures,
        const std::vector<unsigned int>& indices
    );

    void setTextures(const std::vector<TextureBase>& newTextures);

    void bind();
    void unbind();

public:
    std::vector<CGL::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<CGL::TextureBase> textures;

    unsigned int vao, vbo, ebo;
};
}

#endif // MESHBUFFER_H
