#version 330 core
out vec4 FragColor;

in vec2 fTexCoords;
in vec3 fPos;
in vec3 fColor;
in vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // vec3 ambient;
    // vec3 diffuse;
    // vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
};

uniform Material material;
uniform Light lights[3];

void main()
{
    vec3 resultColor;
    vec3 amb ;
    vec3 diff;
    vec3 spec;

    vec4 cameraLight = vec4(1.0);
    float angleSplit = 10; // degree

    for (int i = 0; i < 3; i++) {
        vec3 norm = normalize(fNormal);
        vec3 lightDir = normalize(lights[i].position - fPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 cameraDir = normalize(viewPos - fPos);

        amb = vec3(texture(material.diffuse, fTexCoords));
        diff = vec3(texture(material.diffuse, fTexCoords)) * max(dot(lightDir, norm), 0.0);
        spec = vec3(texture(material.specular, fTexCoords)) * pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);

        // vec3 combColor = (amb + diff + spec) * lights[i].color;
        vec3 combColor = (fColor) * lights[i].color;
        resultColor += combColor;
    }

    // resultColor = (amb + diff + spec) * light.color; // * fColor;

    // FragColor = vec4(resultColor, 1.0);
    FragColor = vec4(resultColor, 1.0);
}

