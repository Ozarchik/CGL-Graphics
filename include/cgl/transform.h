#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CGL {

class Transform {
public:
    Transform();
    Transform(const glm::mat4& mat);

    void reset();

    void scale(float x, float y, float z);
    void scale(float val);
    void scaleX(float val);
    void scaleY(float val);
    void scaleZ(float val);

    void translate(const glm::vec3& pos);
    void translate(float x, float y, float z);
    void translateX(float val);
    void translateY(float val);
    void translateZ(float val);

    void rotate(float angle, float x, float y, float z);

    void ortogonal(float left, float right, float bottom, float top, float near, float far);
    void perspective(float fov, float ratio, float near, float far);

    Transform operator*(const Transform& right) const;
    Transform& operator*=(const Transform& right);

    glm::mat4 data() const;

private:
    glm::mat4 m_matrix;
};
}
