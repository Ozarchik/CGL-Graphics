#ifndef CGL_MESHBUILD_H
#define CGL_MESHBUILD_H

namespace CGL {
class MeshBuilder {
public:
    void setVertices(const std::vector<CGL::Vertex>& vertices);
    void setIndices(const std::vector<unsigned int>& indices);
    void setTextures(const std::vector<CGL::TextureBase>& textures);

    CGL::Mesh build();

private:
    std::vector<CGL::Vectex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<CGL::TextureBase> m_textures;
};
}

#endif