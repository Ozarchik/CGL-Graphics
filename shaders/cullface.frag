#version 330 core

out vec4 FragColor;

in vec2 fTexCoords;

uniform sampler2D texImage;

void main(void)
{
    FragColor = texture(texImage, fTexCoords);
}
