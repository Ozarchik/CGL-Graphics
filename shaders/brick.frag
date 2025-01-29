// #version 330 core

// in VS_OUT {
//     vec3 FragPos;
//     vec2 TexCoords;
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
// } fs_in;

// out vec4 FragColor;

// uniform vec3 lightPos;
// uniform vec3 viewPos;

// uniform sampler2D brick;
// uniform sampler2D brickNormal;

// void main(void)
// {
//     float shiness = 32;

//     vec3 normal = texture(brickNormal, fs_in.TexCoords).rgb;
//     normal = normal * 2.0 - 1.0;
//     // normal = normalize(fs_in.TBN * normal);

//     vec3 brickColor = texture(brick, fs_in.TexCoords).rgb;
//     vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.FragPos);
//     vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.FragPos);

//     vec3 amb = 0.1 * brickColor;
//     vec3 diff = max(dot(lightDir, normal), 0.0) * brickColor;
//     vec3 spec = pow(max(dot(viewDir, reflect(lightDir, normal)), 0.0), shiness) * vec3(0.2);

//     // calc ads ...
//     // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//     FragColor = vec4((amb + diff + spec), 1.0);
//     // FragColor = vec4(1.0);
// }



#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D brick;
uniform sampler2D brickNormal;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
     // obtain normal from normal map in range [0,1]
    vec3 normal = texture(brickNormal, fs_in.TexCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    // get diffuse color
    vec3 color = texture(brick, fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

