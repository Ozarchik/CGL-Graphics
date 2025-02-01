#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 fTex;

uniform mat4 MVP;

void main(void)
{
    fTex = aTex;
    gl_Position = MVP * vec4(aPos, 1.0);
}
