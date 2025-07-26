#pragma once

#include <glad/glad.h>

namespace CGL {

enum ColorType {
    RGB = GL_RGB,
    RGBA = GL_RGBA
};

class Texture
{
public:
    Texture();
    Texture(const char* filename, ColorType colorType = RGB);
    ~Texture();

    void bind();

    void setVerticalFlip(bool status);
    unsigned int id() const;
    void loadImage(const char* filename, ColorType colorType);

private:
    unsigned int m_id;
};
};