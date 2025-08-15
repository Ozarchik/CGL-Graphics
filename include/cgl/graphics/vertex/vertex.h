#pragma once

#include <glm/glm.hpp>

namespace CGL {
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 color;
};
} 
