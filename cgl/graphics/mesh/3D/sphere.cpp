#include <cgl/graphics/mesh/3D/sphere.h>

constexpr int sectors = 300;
constexpr int stacks = 150;
constexpr float radius = 0.5f;

std::vector<cgl::Vertex> genSphereVertices();
std::vector<unsigned int> genSphereIndices();

static const std::vector<cgl::Vertex> sphVertices = genSphereVertices();
static const std::vector<unsigned int> sphIndices = genSphereIndices();

cgl::Sphere::Sphere()
    : Mesh(sphVertices, sphIndices)
{
    m_primitiveData.type = cgl::Primitive::Triangle;
    m_primitiveData.drawType = cgl::DrawType::Indexes;
}

void cgl::Sphere::draw(Shader &shader)
{
    shader.use();
    m_buffer.bind();
    cgl::RenderContext::instance().render(m_primitiveData);
    m_buffer.unbind();
    shader.done();
}

std::vector<cgl::Vertex> genSphereVertices()
{
    std::vector<cgl::Vertex> vertices;

    float sectorStep = 2 * 3.14 / sectors;
    float stackStep = 3.14 / stacks;
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = 3.14 / 2 - i * stackStep; // from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle); // r * cos(u)
        float z = radius * sinf(stackAngle); // r * sin(u)

        for (int j = 0; j <= sectors; ++j) {
            cgl::Vertex v;

            float sectorAngle = j * sectorStep; // from 0 to 2pi
            float x = xy * cosf(sectorAngle); // r * cos(v) * cos(u)
            float y = xy * sinf(sectorAngle); // r * cos(v) * sin(u)
            v.position = glm::vec3(x,y,z);

            float r = (x + radius) / (2 * radius);
            float g = (y + radius) / (2 * radius);
            float b = (z + radius) / (2 * radius);
            v.color = glm::vec3(r,g,b);


            float s = (float)j / sectors;
            float t = (float)i / stacks;
            v.texcoord = glm::vec2(s,t);

            vertices.push_back(v);
        }
    }

    return vertices;
}

std::vector<unsigned int> genSphereIndices()
{
    std::vector<unsigned int> indices;

    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1); // current stack
        int k2 = k1 + sectors + 1; // next stack

        for (int j = 0; j < sectors; ++j) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stacks - 1)) {
                indices.push_back(k2);
                indices.push_back(k2 + 1);
                indices.push_back(k1 + 1);
            }
            k1++;
            k2++;
        }
    }

    return indices;
}
