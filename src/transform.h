#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CGL {

class Transform {
public:
    Transform();
    Transform(const glm::mat4& mat);
    void scale(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);
    void perspective(float fov, float ratio, float near, float far);

    glm::mat4 data() const;

private:
    glm::mat4 m_matrix;
};
};