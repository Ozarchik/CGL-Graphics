#include <cgl/graphics/material/material.h>
#include <glad/glad.h>
#include <format>
#include <iostream>

cgl::Material::Material()
    : m_enabled(false)
{
}

cgl::Material::Material(const std::vector<cgl::Texture>& textures)
    : m_textures(textures), m_enabled(true)
{
}

void cgl::Material::draw(cgl::Shader& shader) {
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    shader.setBool("useTexture", m_enabled); // for test

    for(unsigned int i = 0; i < m_textures.size(); i++) {
        const cgl::Texture& texture = m_textures[i];
        std::string samplerName;

        switch (texture.type) {
        case cgl::TextureType::Diffuse: {
            samplerName = std::format("texture_diffuse{}", diffuseNr++);
        } break;
        case cgl::TextureType::Specular: {
            samplerName = std::format("texture_specular{}", specularNr++);
        } break;
        case cgl::TextureType::Normal: {
            samplerName = std::format("texture_normal{}", normalNr++);
        } break;
        case cgl::TextureType::Height: {
            samplerName = std::format("texture_height{}", heightNr++);
        } break;
        default: {
            samplerName = std::format("texture_height{}", heightNr++);
        }
        }

        shader.setTexture(samplerName, texture.id, i);
    }

    Texture::diactivate2D();
}

void cgl::Material::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void cgl::Material::add(const Texture &texture)
{
    m_textures.push_back(texture);
}
