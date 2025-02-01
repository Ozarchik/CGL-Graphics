#version 330 core

in vec3 fPos;

out vec4 FragColor;

uniform vec3 timeColor;

void main(void)
{
    FragColor = vec4(timeColor, 1.0);
}
