#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"

namespace CGL {
struct Light {
    glm::vec3 pos;
    glm::vec3 color;
};
}
