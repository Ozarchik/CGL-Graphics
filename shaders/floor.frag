#version 330 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D floorTexture;

void main(void)
{
    vec3 color = vec3(texture(floorTexture, fTex));
    FragColor = vec4(mix(vec3(0.2), color, 0.5), 1.0);
}
