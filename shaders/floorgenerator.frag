#version 330 core

in vec3 fColor;
out vec4 FragColor;

void main(void)
{
   FragColor = vec4(1.0, 1.0, 1.0, 1.0);   
   // FragColor = vec4(fColor, 1.0);   
}
