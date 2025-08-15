#ifndef CGL_MATERIAL_H
#define CGL_MATERIAL_H

#include <vector>
#include <cgl/graphics/vertex/vertex.h>
#include <cgl/graphics/texture/texture.h>
#include <cgl/graphics/shader.h>

namespace CGL {
class Material {
    friend class MaterialBuilder;

public:
    Material();
    explicit Material(const std::vector<CGL::Texture>& textures);
    CGL::Material& operator=(const CGL::Material& other) {
        m_textures = other.m_textures;
        m_enabled = other.m_enabled;
        return *this;
    }

    void draw(CGL::Shader& shader);

    void setEnabled(bool enabled);

private:
    void add(const CGL::Texture& texture);

private:
    std::vector<CGL::Texture> m_textures;
    bool m_enabled = false;
};
}

#endif
