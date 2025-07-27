#ifndef CGL_MESHBUILD_H
#define CGL_MESHBUILD_H

#include <vector>
#include <cgl/vertex.h>
#include <cgl/texture/texturebase.h>
#include <cgl/mesh/common/mesh.h>

namespace CGL {
class MeshBuilder {
public:
    MeshBuilder() = default;
    void setVertices(const std::vector<CGL::Vertex>& vertices);
    void setIndices(const std::vector<unsigned int>& indices);
    void setTextures(const std::vector<CGL::TextureBase>& textures);

    CGL::Mesh build();

private:
    std::vector<CGL::Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<CGL::TextureBase> m_textures;
};
}

#endif