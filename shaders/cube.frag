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
uniform Light lights[3];

float near = 0.1;
float far = 1.0;

vec3 toonShade()
{
    vec3 resultColor;
    vec3 amb ;
    vec3 diff;
    vec3 spec;

    const int levels = 3;
    const float scaleFactor = 1.0 / levels;

    for (int i = 0; i < 3; i++) {
        vec3 s =  normalize(lights[i].position - fPos);
        float cosine = max(0.0, dot(s, fNormal));
        vec3 diffuse = floor(cosine * levels) * scaleFactor * lights[i].color;

        resultColor += diffuse;
    }

    return resultColor;
}

float linearDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    vec3 resultColor;
    vec3 amb ;
    vec3 diff;
    vec3 spec;

    vec4 cameraLight = vec4(1.0);
    float angleSplit = 10; // degree

    bool toonShadeMode = false;

    if (toonShadeMode) {
        resultColor = toonShade();
    } else {
        for (int i = 0; i < 3; i++) {
            vec3 norm = normalize(fNormal);
            vec3 lightDir = normalize(lights[i].position - fPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            vec3 cameraDir = normalize(viewPos - fPos);

            amb = vec3(texture(material.diffuse, fTexCoords));
            diff = vec3(texture(material.diffuse, fTexCoords)) * max(dot(lightDir, norm), 0.0);
            spec = vec3(texture(material.specular, fTexCoords)) * pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);

            vec3 combColor = (amb + diff + spec) * lights[i].color;
            // vec3 combColor = (fColor) * lights[i].color;
            resultColor += combColor;
        }

        float depth = min(pow(linearDepth(gl_FragCoord.z) / far, 0.5), 1);
    }

    // FragColor = vec4(vec3(resultColor), 1.0);

    FragColor = vec4(resultColor, 1.0);
}

