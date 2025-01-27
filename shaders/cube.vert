#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

out vec2 fTexCoords;
out vec3 fPos;
out vec3 fColor;
out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fTexCoords = aTexCoords;

    fPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(fPos, 1.0);

    fNormal = mat3(transpose(inverse(model))) * aNormal;
    fColor = aColor;
}
