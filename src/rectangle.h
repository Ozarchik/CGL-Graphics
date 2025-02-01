#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>

#include "mesh.h"
#include "vertexbuffer.h"

namespace CGL {
class Rectangle: public CGL::Mesh
{
public:
    Rectangle();
    Rectangle(const CGL::TextureBase& texture);

    void draw(Shader &shader);

private:
    std::vector<CGL::Vertex> vertices {
        // x/y/z         r/g/b          s/t
        CGL::Vertex{glm::vec3(-1.0,  1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(1.0, 1.0, 1.0)},
        CGL::Vertex{glm::vec3(-1.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)},
        CGL::Vertex{glm::vec3( 1.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(1.0, 1.0, 1.0)},

        CGL::Vertex{glm::vec3( 1.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(1.0, 1.0, 1.0)},
        CGL::Vertex{glm::vec3( 1.0,  1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(1.0, 1.0, 1.0)},
        CGL::Vertex{glm::vec3(-1.0,  1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(1.0, 1.0, 1.0)}
    };

    CGL::VertexBuffer m_vertexBuffer;
};
}

#endif // RECTANGLE_H
