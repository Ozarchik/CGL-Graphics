#ifndef CGL_MATERIAL_H
#define CGL_MATERIAL_H

#include <vector>
#include <cgl/vertex.h>
#include <cgl/texture/texture.h>
#include <cgl/shader.h>

namespace CGL {
class Material {
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
    std::vector<CGL::Texture> m_textures;
    bool m_enabled = false;
};
}

#endif
