#include <cgl/Material.h>
#include <glad/glad.h>

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
        std::string number;
        std::string name = texture.type;

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        else if(name == "texture_normal")
            number = std::to_string(normalNr++);
        else if(name == "texture_height")
            number = std::to_string(heightNr++);
        else {
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
        }

        shader.setInt((name + number).c_str(), i);

        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);
}
