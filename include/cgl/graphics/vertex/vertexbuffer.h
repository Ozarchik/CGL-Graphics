#ifndef CGL_VERTEXBUFFER_H
#define CGL_VERTEXBUFFER_H

#include <vector>
#include <cgl/graphics/vertex/vertex.h>

namespace cgl {
class VertexBuffer
{
public:
    VertexBuffer() = default;
    VertexBuffer(const std::vector<cgl::Vertex>& vertices);
    void use();
    void done();

private:
    unsigned int vbo, vao, tex;
};
}

#endif // CGL_VERTEXBUFFER_H
