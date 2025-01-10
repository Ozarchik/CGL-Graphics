#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string>

CGL::Texture::Texture()
{
}

CGL::Texture::Texture(const char* filename, ColorType colorType)
{
    loadImage(filename, colorType);
}

CGL::Texture::~Texture()
{
}

void CGL::Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

unsigned int CGL::Texture::id() const
{
    return m_id;
}

void CGL::Texture::loadImage(const char* filename, ColorType colorType)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) {
        std::cout << "Failed to load texture image" << std::endl;
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

void CGL::Texture::setVerticalFlip(bool status)
{
    stbi_set_unpremultiply_on_load(status);
}

