#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include <vector>
#include <cgl/vertex.h>
#include <cgl/shader.h>

namespace CGL {
struct MeshBuffer
{
public:
    MeshBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void bind(CGL::Shader* shader = nullptr);
    void unbind();

public:
    std::vector<CGL::Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int vao, vbo, ebo;
};
}

#endif // MESHBUFFER_H
