#ifndef CGL_MESHBUFFER_H
#define CGL_MESHBUFFER_H

#include <vector>
#include <cgl/core/buffer/vaobuffer.h>
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

    void setVAO(VAOBuffer&& vao);

public:
    // CGL::PrimitiveData m_primitive;
    std::vector<CGL::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    CGL::VAOBuffer m_vao;
    unsigned int vao, vbo, ebo;
};
}

#endif // CGL_MESHBUFFER_H
