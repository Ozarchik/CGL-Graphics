#version 330 core

in vec2 fTex;

out vec4 FragColor;

uniform sampler2D floorTexture;
uniform sampler2D brickTexture;

void main(void)
{
    vec3 floorColor = vec3(texture(floorTexture, fTex));
    vec3 brickColor = vec3(texture(brickTexture, fTex));


    if (gl_FrontFacing) {
        FragColor = vec4(brickColor, 1.0); //*/vec4(mix(vec3(floorColor), vec3(brickColor), 0.8), 1.0);
    } else {
        FragColor = vec4(floorColor, 1.0); // vec4(mix(vec3(floorColor), vec3(brickColor), 0.8), 1.0);
    }

    // if (gl_FragCoord.x > 400 && gl_FragCoord.x < 500) {
    //     FragColor = vec4(0.5, 0.1, 0.5, 1.0);
    // } else {
    //     FragColor = vec4(mix(vec3(0.2), color, 0.5), 1.0);
    // }
}
