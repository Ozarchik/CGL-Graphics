#include <cgl/graphics/texture/textureloader.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

cgl::Texture cgl::TextureLoader::loadFromFile(const std::string &filepath, bool flipVertical)
{
    if (m_loadedTextures.count(filepath)) {
        return m_loadedTextures[filepath];
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);

    StbiImage stbiImage(filepath, flipVertical);
    if (!stbiImage.isValid())
        return {};


    TextureData textureData = stbiImage.makeTextureData();

    GLenum format = 0;
    if (textureData.components == 1)
        format = GL_RED;
    else if (textureData.components == 3)
        format = GL_RGB;
    else if (textureData.components == 4) {
        format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.width, textureData.height, 0, format, GL_UNSIGNED_BYTE, textureData.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_loadedTextures[filepath] = cgl::Texture{textureID};

    cgl::Texture texture;
    texture.id = textureID;
    texture.size = {textureData.width, textureData.height};
    return texture;
}

cgl::TextureData cgl::TextureLoader::getTextureData(const std::string &filepath, bool flipVertical)
{
    StbiImage stbiImage(filepath, flipVertical);
    return stbiImage.makeTextureData();
}

unsigned int cgl::TextureLoader::loadCubmap(const std::string &dir, const std::vector<std::string>& faces)
{
    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    auto texImage2D = [](const TextureData& texData, int coord) {
        glTexImage2D (
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + coord, 0,
            GL_RGB, texData.width, texData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData.data.data()
        );
    };

    for (unsigned int i = 0; i < faces.size(); i++) {
        StbiImage image(dir + "/" + faces[i]);

        texImage2D(image.makeTextureData(), i);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texId;
}

cgl::TextureLoader::StbiImage::StbiImage(const std::string &path, bool flipVerticaly)
    : width(0), height(0), components(0)
{
    stbi_set_flip_vertically_on_load(flipVerticaly);
    data = stbi_load(path.c_str(), &width, &height, &components, 0);
    if (!data) {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }
}

cgl::TextureLoader::StbiImage::~StbiImage() {
    stbi_image_free(data);
}

bool cgl::TextureLoader::StbiImage::isValid()
{
    return data != nullptr;
}

cgl::TextureData cgl::TextureLoader::StbiImage::makeTextureData()
{
    unsigned int bytes = width*height*components;

    TextureData result {
        .data = std::vector<unsigned char>(data, data+bytes),
        .width = width,
        .height = height,
        .components = components
    };

    return result;
}
