#include <cgl/graphics/texture/texturebuilder.h>

CGL::TextureBuilder &CGL::TextureBuilder::setMinFilter(int param)
{
    return *this;
}

CGL::TextureBuilder &CGL::TextureBuilder::setImage(int width, int height, const void *data)
{
    return *this;
}

CGL::TextureBuilder &CGL::TextureBuilder::setMagFilter(int param)
{
    return *this;
}

CGL::Texture CGL::TextureBuilder::done()
{
    return {};
}

CGL::TextureBuilder::TextureBuilder() {}

CGL::TextureBuilder CGL::TextureBuilder::build()
{
    return TextureBuilder();
}
