#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include <cgl/vertex.h>

namespace CGL {
class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(const std::vector<CGL::Vertex>& vertices);
    void use();
    void done();

private:
    unsigned int vbo, vao, tex;
};
}

#endif // VERTEXBUFFER_H
