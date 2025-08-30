#ifndef CGL_TEXTURE_H
#define CGL_TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace CGL {

enum class TextureType {
    Diffuse,
    Specular,
    Normal,
    Height
};

enum TextureFilter {
    Linear = GL_LINEAR
};

enum TextureWrap {
    EdgeClamp = GL_CLAMP_TO_EDGE
};

struct Texture {
    unsigned int id = -1;
    TextureType type = TextureType::Diffuse;
    std::string path = "";
    glm::vec2 size;

    static void bind2D(unsigned int id);
    static void bind2D(unsigned int id, int unit);
    static void unbind2D(int unit);
    static void activate2D(int unit);
    static void diactivate2D();
    static void filter2D(CGL::TextureFilter min, CGL::TextureFilter max);
    static void wrap2D(CGL::TextureWrap sWrap, CGL::TextureWrap tWrap);
};
}

#endif
