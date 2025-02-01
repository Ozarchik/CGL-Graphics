#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>
#include "vertex.h"

namespace CGL {
class VertexBuffer
{
public:
    VertexBuffer(const std::vector<CGL::Vertex>& vertices);
    void use();

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int TEX;
};
}

#endif // VERTEXBUFFER_H
