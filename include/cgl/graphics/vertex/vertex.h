#pragma once

#include <glm/glm.hpp>

namespace cgl {
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 color;
};
} 
