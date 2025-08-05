#version 330 core

in vec3 fColor;
out vec4 FragColor;

uniform float gradient;

void main(void)
{
   FragColor = vec4(gradient*0.3, gradient*0.3, gradient, 1.0);
}
