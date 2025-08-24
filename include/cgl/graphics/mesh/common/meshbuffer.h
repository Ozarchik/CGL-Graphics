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

    MeshBuffer(MeshBuffer&& other) = default;
    MeshBuffer& operator=(MeshBuffer&& other) = default;

    void bind(CGL::Shader* shader = nullptr);
    void unbind();

    void setVAO(VAOBuffer&& vao);

public:
    CGL::VAOBuffer m_vao;
    std::vector<CGL::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
}

#endif // CGL_MESHBUFFER_H
