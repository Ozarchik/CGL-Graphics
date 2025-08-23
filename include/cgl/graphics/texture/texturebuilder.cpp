#include <cgl/graphics/texture/texturebuilder.h>
#include <glad/glad.h>



CGL::TextureBuilder::TextureBuilder()
{
    glGenTextures(1, &m_texture.id);
    glBindTexture(GL_TEXTURE_2D, m_texture.id);
}

CGL::TextureBuilder CGL::TextureBuilder::build()
{
    return TextureBuilder();
}

CGL::TextureBuilder& CGL::TextureBuilder::setMinFilter(int param)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    return *this;
}

CGL::TextureBuilder& CGL::TextureBuilder::setMagFilter(int param)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    return *this;
}

CGL::TextureBuilder &CGL::TextureBuilder::setImage(int width, int height, const void *data)
{
    glTexImage2D(GL_TEXTURE_2D, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    return *this;
}

CGL::Texture CGL::TextureBuilder::done()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    return std::move(m_texture);
}

