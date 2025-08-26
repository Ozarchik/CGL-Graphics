#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    FragColor = vec4(mix(texture(screenTexture, TexCoords).rgb, vec3(0.2, 0.5, 0.5), 0.5), 0.5);
}
