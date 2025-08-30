#include <cgl/graphics/texture/texturebuilder.h>

cgl::TextureBuilder &cgl::TextureBuilder::setMinFilter(int param)
{
    return *this;
}

cgl::TextureBuilder &cgl::TextureBuilder::setImage(int width, int height, const void *data)
{
    return *this;
}

cgl::TextureBuilder &cgl::TextureBuilder::setMagFilter(int param)
{
    return *this;
}

cgl::Texture cgl::TextureBuilder::done()
{
    return {};
}

cgl::TextureBuilder::TextureBuilder() {}

cgl::TextureBuilder cgl::TextureBuilder::build()
{
    return TextureBuilder();
}
