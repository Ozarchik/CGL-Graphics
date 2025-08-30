#include <cgl/graphics/texture/texture.h>

void CGL::Texture::bind2D(unsigned int id)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void CGL::Texture::bind2D(unsigned int id, int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void CGL::Texture::unbind2D(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CGL::Texture::activate2D(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
}

void CGL::Texture::diactivate2D()
{
    glActiveTexture(GL_TEXTURE0);
}

void CGL::Texture::filter2D(CGL::TextureFilter min, CGL::TextureFilter max)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
}

void CGL::Texture::wrap2D(CGL::TextureWrap sWrap, CGL::TextureWrap tWrap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}
