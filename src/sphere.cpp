#include "sphere.h"

const int sectors = 36; // Number of sectors
const int stacks = 18;  // Number of stacks
const float radius = 1.0f;

CGL::Sphere::Sphere()
    : Mesh()
{
    // for (int i = 0; i <= stacks; ++i) {
    //     float stackAngle = M_PI / 2 - i * M_PI / stacks; // from pi/2 to -pi/2
    //     float xy = radius * cosf(stackAngle); // r * cos(u)
    //     float z = radius * sinf(stackAngle); // r * sin(u)

    //     for (int j = 0; j <= sectors; ++j) {
    //         float sectorAngle = j * 2 * M_PI / sectors; // from 0 to 2pi
    //         float x = xy * cosf(sectorAngle); // r * cos(v) * cos(u)
    //         float y = xy * sinf(sectorAngle); // r * cos(v) * sin(u)

    //         Vertex v;
    //         v.position.x = x;
    //         v.position.y = y;
    //         v.position.z = z;


    //         float r = (x + radius) / (2 * radius);
    //         float g = (y + radius) / (2 * radius);
    //         float b = (z + radius) / (2 * radius);
    //         colors.push_back(r);
    //         colors.push_back(g);
    //         colors.push_back(b);


    //         m_vertices.push_back(v);
    //     }
    // }

    // for (int i = 0; i < stacks; ++i) {
    //     int k1 = i * (sectors + 1); // current stack
    //     int k2 = k1 + sectors + 1; // next stack

    //     for (int j = 0; j < sectors; ++j) {
    //         if (i != 0) {
    //             m_indices.push_back(k1);
    //             m_indices.push_back(k2);
    //             m_indices.push_back(k1 + 1);
    //         }
    //         if (i != (stacks - 1)) {
    //             m_indices.push_back(k2);
    //             m_indices.push_back(k2 + 1);
    //             m_indices.push_back(k1 + 1);
    //         }
    //         k1++;
    //         k2++;
    //     }
    // }

    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);


    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // m_colorBuffer.setVector(colors, CGL::VertexBufferType);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
    // glEnableVertexAttribArray(3);
}

void CGL::Sphere::draw(Shader &shader)
{
    // glBindVertexArray(VAO);
    // // glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertices.size());
    // glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
}
