#ifndef CGL_MESHBUFFER_H
#define CGL_MESHBUFFER_H

#include <memory>
#include <vector>
#include <cgl/core/buffer/vaobuffer.h>
#include <cgl/graphics/vertex/vertex.h>
#include <cgl/graphics/shader.h>

namespace cgl {
struct MeshBuffer
{
    friend class MeshBuilder;

public:
    MeshBuffer();
    MeshBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~MeshBuffer();

    MeshBuffer(MeshBuffer&& other) = default;
    MeshBuffer& operator=(MeshBuffer&& other) = default;

    void bind(cgl::Shader* shader = nullptr);
    void unbind();

    void setVAO(std::unique_ptr<VAOBuffer> &&vao);

public:
    std::unique_ptr<cgl::VAOBuffer> m_vao;
    std::vector<cgl::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
}

#endif // CGL_MESHBUFFER_H
