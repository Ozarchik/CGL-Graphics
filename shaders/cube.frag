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
uniform vec3 viewDir;
uniform bool gammaEnabled;

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

struct LightBolb {
    vec3 intensity;
    float exponent;
    float cutoff;
};

uniform Material material;
uniform Light light;
uniform sampler2D diffuseTex;

void main()
{
    vec3 amb, diff, spec;

    vec3 norm = normalize(fNormal);

    vec3 lightDir = normalize(light.position - fPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(viewPos - fPos);

    vec3 texColor = vec3(texture(diffuseTex, fTexCoords));

    amb  = texColor * 1;
    diff = texColor * max(dot(lightDir, norm), 0.0) * 1;
    vec3 halfWayDir = normalize(lightDir + viewDir);
    spec = texColor * pow(max(dot(norm, halfWayDir), 0.0), 32);

    vec3 combColor = (amb + diff + spec) * light.color;

    float attenuation = 1.0/length(viewPos - fPos);

    if (gammaEnabled) {
        float gamma = 2.2;
        FragColor.rgb = pow(attenuation * combColor, vec3(1.0/gamma));
    } else {
        FragColor = attenuation * vec4(combColor, 1.0);
    }

    // FragColor = texture(diffuseTex, fTexCoords);
}

