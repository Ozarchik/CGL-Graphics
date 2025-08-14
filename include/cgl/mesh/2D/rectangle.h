#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>

#include <cgl/mesh/common/mesh.h>
#include <cgl/vertexbuffer.h>

namespace CGL {
class Rectangle: public CGL::Mesh
{
public:
    Rectangle();
    Rectangle(glm::vec3 color);

    void draw(Shader &shader);

private:
    glm::vec3 m_color;
    std::vector<CGL::Vertex> vertices {
        /* position                             normal                    texture              color                  */
        CGL::Vertex{glm::vec3(-0.5,  0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(m_color)},
        CGL::Vertex{glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(m_color)},
        CGL::Vertex{glm::vec3( 0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(m_color)},

        CGL::Vertex{glm::vec3( 0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(m_color)},
        CGL::Vertex{glm::vec3( 0.5,  0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(m_color)},
        CGL::Vertex{glm::vec3(-0.5,  0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(m_color)}
    };

    CGL::VertexBuffer m_vertexBuffer;
};
}

#endif // RECTANGLE_H
