#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <cgl/texture/texturebase.h>
#include <cgl/stb_image.h>

#include <glad/glad.h>
#include <vector>
#include <string>

namespace CGL {
class TextureLoader
{
public:
    TextureLoader() = default;

    static CGL::TextureBase loadFromFile(const std::string &filepath, bool flipVertical = false);
    static unsigned int loadCubmap(const std::string &dir, const std::vector<std::string> &faces);
};
}

#endif // TEXTURELOADER_H
