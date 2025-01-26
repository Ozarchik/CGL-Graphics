#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"

namespace CGL {
class Light {
public:
    Light() = default;
    Light(const glm::vec3& position, const glm::vec3& color);

    void setup(Shader& Shader);
    
private:
    glm::vec3 m_pos;
    glm::vec3 m_color;
};
};
