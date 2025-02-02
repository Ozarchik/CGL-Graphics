#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 normal;
} fs_in;

uniform sampler2D diffuse_1;

void main() {
    // if (gl_FragCoord.x > 300 && gl_FragCoord.x < 400
        // && gl_FragCoord.y > 300 && gl_FragCoord.y < 400
        // ) {
        // FragColor = vec4(1.0, 0.0, 0.5, 1.0);
    // } else {
        // FragColor = vec4(1.0, 1.0, 0.5, 1.0);
    // }

    // FragColor = texture(diffuse_1, fs_in.texCoord);
    // FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    FragColor = vec4(0.0, 1.0, 1.0, 1.0);
}
