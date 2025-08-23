#ifndef CGL_TEXTURE_H
#define CGL_TEXTURE_H

#include <string>
#include <glm/glm.hpp>

namespace CGL {

enum class TextureType {
    Diffuse,
    Specular,
    Normal,
    Height
};

struct Texture {
    unsigned int id = -1;
    TextureType type = TextureType::Diffuse;
    std::string path = "";
    glm::vec2 size;
};
}

#endif
