#ifndef CGL_TEXTURELOADER_H
#define CGL_TEXTURELOADER_H

#include <cgl/graphics/texture/texture.h>

#include <glad/glad.h>
#include <vector>
#include <string>
#include <unordered_map>

namespace cgl {
class TextureLoader
{
public:
    TextureLoader() = default;

    static cgl::Texture loadFromFile(const std::string &filepath, bool flipVertical = false);
    static unsigned int loadCubmap(const std::string &dir, const std::vector<std::string> &faces);
    std::tuple<std::vector<unsigned char>, glm::vec3> getSourceData(const std::string &filepath, bool flipVertical = false);

private:
    inline static std::unordered_map<std::string, cgl::Texture> m_loadedTextures;
};
}

#endif // CGL_TEXTURELOADER_H
