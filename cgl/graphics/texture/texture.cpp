#include <cgl/graphics/texture/texture.h>

void cgl::Texture::bind2D(unsigned int id)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void cgl::Texture::bind2D(unsigned int id, int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void cgl::Texture::unbind2D(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void cgl::Texture::activate2D(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
}

void cgl::Texture::diactivate2D()
{
    glActiveTexture(GL_TEXTURE0);
}

void cgl::Texture::filter2D(cgl::TextureFilter min, cgl::TextureFilter max)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
}

void cgl::Texture::wrap2D(cgl::TextureWrap sWrap, cgl::TextureWrap tWrap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}
