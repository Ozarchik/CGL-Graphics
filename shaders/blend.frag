#version 330 core

in vec2 fTexCoords;
out vec4 FragColor;

uniform sampler2D grassTexture;

void main(void)
{
    vec4 texColor = texture(grassTexture, fTexCoords);
    // if (texColor.a < 0.1)
    //     discard;

    FragColor = texColor;
}
