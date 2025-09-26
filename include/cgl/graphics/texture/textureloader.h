#ifndef CGL_TEXTURELOADER_H
#define CGL_TEXTURELOADER_H

#include <cgl/graphics/texture/texture.h>

#include <glad/glad.h>
#include <vector>
#include <string>
#include <unordered_map>

namespace cgl {

struct TextureData {
    std::vector<unsigned char> data;
    int width;
    int height;
    int components;
};

class TextureLoader
{
public:
    TextureLoader() = default;

    static cgl::Texture loadFromFile(const std::string &filepath, bool flipVertical = false);
    static unsigned int loadCubmap(const std::string &dir, const std::vector<std::string> &faces);
    TextureData getTextureData(const std::string &filepath, bool flipVertical = false);

private:
    class StbiImage {
    public:
        StbiImage(const std::string& path, bool flipVerticaly = true);
        ~StbiImage();
        bool isValid();

        TextureData makeTextureData();

    private:
        unsigned char* data = nullptr;
        int width;
        int height;
        int components;
    };

private:
    inline static std::unordered_map<std::string, cgl::Texture> m_loadedTextures;
};
}

#endif // CGL_TEXTURELOADER_H
