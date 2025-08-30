#ifndef CGL_MATERIAL_H
#define CGL_MATERIAL_H

#include <vector>
#include <cgl/graphics/vertex/vertex.h>
#include <cgl/graphics/texture/texture.h>
#include <cgl/graphics/shader.h>

namespace cgl {
class Material {
    friend class MaterialBuilder;

public:
    Material();
    explicit Material(const std::vector<cgl::Texture>& textures);
    cgl::Material& operator=(const cgl::Material& other) {
        m_textures = other.m_textures;
        m_enabled = other.m_enabled;
        return *this;
    }

    void draw(cgl::Shader& shader);

    void setEnabled(bool enabled);
    void bindTexture(Shader &shader, const Texture &texture, int samplerNum);

private:
    void add(const cgl::Texture& texture);

private:
    std::vector<cgl::Texture> m_textures;
    bool m_enabled = false;
};
}

#endif
