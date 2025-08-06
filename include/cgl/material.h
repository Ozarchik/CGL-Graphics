#ifndef CGL_MATERIAL_H
#define CGL_MATERIAL_H

#include <vector>
#include <cgl/vertex.h>
#include <cgl/texture/texture.h>
#include <cgl/shader.h>

namespace CGL {
class Material {
public:
    explicit Material();
    explicit Material(const std::vector<CGL::Texture>& textures);
    CGL::Material& operator=(const CGL::Material& other) {
        m_textures = other.m_textures;
        return *this;
    }

    void draw(CGL::Shader& shader);

private:
    std::vector<CGL::Texture> m_textures;
};
}

#endif
