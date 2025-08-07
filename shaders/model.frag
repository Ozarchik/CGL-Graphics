#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform bool selected;


void main(void)
{
    if (selected)
        FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    else
        FragColor = texture(texture_diffuse1, TexCoords);
}

