#ifndef CGL_TEXTURELOADER_H
#define CGL_TEXTURELOADER_H

#include <cgl/graphics/texture/texture.h>

#include <glad/glad.h>
#include <vector>
#include <string>
#include <unordered_map>

namespace CGL {
class TextureLoader
{
public:
    TextureLoader() = default;

    static CGL::Texture loadFromFile(const std::string &filepath, bool flipVertical = false);
    static unsigned int loadCubmap(const std::string &dir, const std::vector<std::string> &faces);

private:
    inline static std::unordered_map<std::string, CGL::Texture> m_loadedTextures;
};
}

#endif // CGL_TEXTURELOADER_H
