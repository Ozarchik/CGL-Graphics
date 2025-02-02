#pragma once

#include <glad/glad.h>
#include <string>

#include "stb_image.h"
#include <iostream>

namespace CGL {
struct TextureBase {
    unsigned int id;
    std::string type;
    std::string path;

    static TextureBase create(const std::string &filepath, const std::string& name) {
        TextureBase texture = loadFromFile(filepath);
        texture.type = name;
        texture.path = filepath;
        return texture;
    }

    static TextureBase loadFromFile(const std::string &filepath, bool flipVertical = false)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        stbi_set_flip_vertically_on_load(flipVertical);
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
        } else {
            std::cout << "Texture failed to load at path: " << filepath << std::endl;
            stbi_image_free(data);
        }

        stbi_set_flip_vertically_on_load(false);

        TextureBase tex;
        tex.id = textureID;
        return tex;
    }

    static unsigned int loadCubmap(const std::string &dir, const std::vector<std::string>& faces)
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
};
}
