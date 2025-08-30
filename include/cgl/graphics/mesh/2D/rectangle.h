#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>

#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/graphics/vertex/vertexbuffer.h>

namespace cgl {
class Rectangle: public cgl::Mesh
{
public:
    Rectangle();
    Rectangle(glm::vec3 color);

    void draw(Shader &shader);

private:
    glm::vec3 m_color;
    std::vector<cgl::Vertex> vertices {
        /* position                             normal                    texture              color                  */
        cgl::Vertex{glm::vec3(-1.0,  1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(m_color)},
        cgl::Vertex{glm::vec3(-1.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(m_color)},
        cgl::Vertex{glm::vec3( 1.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(m_color)},

        cgl::Vertex{glm::vec3( 1.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(m_color)},
        cgl::Vertex{glm::vec3( 1.0,  1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(m_color)},
        cgl::Vertex{glm::vec3(-1.0,  1.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(m_color)}
    };

    cgl::VertexBuffer m_vertexBuffer;
};
}

#endif // RECTANGLE_H
