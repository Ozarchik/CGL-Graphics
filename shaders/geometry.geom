#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 64) out;

uniform float time;

void build_house(vec4 position)
{
    gl_Position = position + vec4(-2, -2, 0.0, 0.0);    // 1:bottom-left
    EmitVertex();
    gl_Position = position + vec4( 2, -2, 0.0, 0.0);    // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-2,  2, 0.0, 0.0);    // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 2,  2, 0.0, 0.0);    // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0,  4, 0.0, 0.0);    // 5:top
    EmitVertex();
    EndPrimitive();
}

vec3 getNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a,b));
}

vec4 explode(vec4 pos, vec3 normal)
{
    float magn = 2.0;
    vec3 dir = normal * ((sin(time) + 1.0)/2.0)*magn;
    return pos + vec4(dir, 1.0);
}

void createExplodeObj(vec3 offs)
{
    vec3 normal = getNormal();

    gl_Position = explode(gl_in[0].gl_Position + vec4(offs, 1.0), normal);
    EmitVertex();

    gl_Position = explode(gl_in[1].gl_Position + vec4(offs, 1.0), normal);
    EmitVertex();

    gl_Position = explode(gl_in[2].gl_Position + vec4(offs, 1.0), normal);
    EmitVertex();
}

void main(void)
{
    createExplodeObj(vec3(0.0, 0.0, 0.0));
    EndPrimitive();
    createExplodeObj(vec3(0.0, 20.0, 0.0));
    EndPrimitive();
    createExplodeObj(vec3(0.0, -20.0, 0.0));
    EndPrimitive();
    createExplodeObj(vec3(20.0, 0.0, 0.0));
    EndPrimitive();
    createExplodeObj(vec3(-20.0, 0.0, 0.0));
    EndPrimitive();
}
