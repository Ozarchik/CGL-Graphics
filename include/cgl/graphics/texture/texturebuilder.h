#ifndef CGL_TEXTUREBUILDER_H
#define CGL_TEXTUREBUILDER_H

#include <cgl/graphics/texture/texture.h>

namespace cgl {
class TextureBuilder
{
public:
    TextureBuilder build();
    TextureBuilder& setMinFilter(int param);
    TextureBuilder& setMagFilter(int param);
    TextureBuilder& setImage(int width, int height, const void* data);
    Texture done();

private:
    TextureBuilder();

private:
    Texture m_texture;
};
}

#endif // CGL_TEXTUREBUILDER_H
