#include <cgl/graphics/texture/textureloader.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

CGL::Texture CGL::TextureLoader::loadFromFile(const std::string &filepath, bool flipVertical)
{
    if (m_loadedTextures.count(filepath)) {
        return m_loadedTextures[filepath];
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        m_loadedTextures[filepath] = CGL::Texture{textureID};
    } else {
        std::cout << "Texture failed to load at path: " << filepath << std::endl;
        stbi_image_free(data);
        return {};
    }

    // stbi_set_flip_vertically_on_load(false);

    CGL::Texture texture;
    texture.id = textureID;
    texture.size = {width, height};
    return texture;
}

std::tuple<std::vector<unsigned char>, glm::vec3> CGL::TextureLoader::getSourceData(const std::string &filepath, bool flipVertical)
{
    int width, height, nrComponents;

    std::tuple<std::vector<unsigned char>, glm::vec3> result;
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (!data)
        return {};


    int bytes = width*height*nrComponents;
    std::vector<unsigned char> resultData(data, data+bytes);
    result = {std::move(resultData), glm::vec3(width,height,nrComponents)};

    stbi_image_free(data);

    return result;
}

unsigned int CGL::TextureLoader::loadCubmap(const std::string &dir, const std::vector<std::string>& faces)
{
    unsigned int texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    int w, h, channels;
    unsigned char* data;

    for (unsigned int i = 0; i < faces.size(); i++) {
        data = stbi_load((dir + "/" + faces[i]).c_str(), &w, &h, &channels, 0);
        glTexImage2D (
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data
        );

        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texId;
}
