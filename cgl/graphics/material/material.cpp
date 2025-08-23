#include <cgl/graphics/material/material.h>
#include <glad/glad.h>
#include <format>

CGL::Material::Material()
    : m_enabled(false)
{
}

CGL::Material::Material(const std::vector<CGL::Texture>& textures)
    : m_textures(textures), m_enabled(true)
{
}

void CGL::Material::draw(CGL::Shader& shader) {
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    shader.setBool("useTexture", m_enabled); // for test

    for(unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        CGL::Texture texture = m_textures[i];
        std::string samplerName;

        switch (texture.type) {
        case CGL::TextureType::Diffuse: {
            samplerName = std::format("texture_diffuse{}", diffuseNr++);
        } break;
        case CGL::TextureType::Specular: {
            samplerName = std::format("texture_specular{}", specularNr++);
        } break;
        case CGL::TextureType::Normal: {
            samplerName = std::format("texture_normal{}", normalNr++);
        } break;
        case CGL::TextureType::Height: {
            samplerName = std::format("texture_height{}", heightNr++);
        } break;
        default: {
            samplerName = std::format("texture_height{}", heightNr++);
        }
        }

        shader.setInt(samplerName, i);

        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);
}

void CGL::Material::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void CGL::Material::add(const Texture &texture)
{
    m_textures.push_back(texture);
}
