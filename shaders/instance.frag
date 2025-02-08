#version 330 core

in vec2 TexCoords;
in vec3 fColor;

out vec4 FragColor;

// uniform vec3 rockColor;
uniform sampler2D texture_diffuse1;

void main(void)
{
    // FragColor = vec4(rockColor, 1.0);
    FragColor = texture(texture_diffuse1, TexCoords);
    FragColor += vec4(1.0, 1.0, 1.0, 1.0);
}
