#ifndef CGL_MESHBUFFER_H
#define CGL_MESHBUFFER_H

#include <vector>
#include <cgl/graphics/vertex/vertex.h>
#include <cgl/graphics/shader.h>

namespace CGL {
struct MeshBuffer
{
    friend class MeshBuilder;

public:
    MeshBuffer();
    ~MeshBuffer();
    MeshBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void bind(CGL::Shader* shader = nullptr);
    void unbind();

private:
    void setVertices(const std::vector<CGL::Vertex>& vertices);
    void setIndices(const std::vector<unsigned int>& indices);

public:
    // CGL::PrimitiveData m_primitive;
    std::vector<CGL::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    unsigned int vao, vbo, ebo;
};
}

#endif // CGL_MESHBUFFER_H
