#version 330 core

in vec3 texCoords;
out vec4 FragColor;

uniform samplerCube skybox;

void main(void)
{
    FragColor = texture(skybox, texCoords);
}
