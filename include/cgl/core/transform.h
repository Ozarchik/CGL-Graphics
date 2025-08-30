#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cgl {

class Transform {
public:
    Transform();
    Transform(const glm::mat4& mat);

    cgl::Transform clone() const;

    cgl::Transform& reset();
    cgl::Transform& scale(float val);
    cgl::Transform& scale(float x, float y, float z);
    cgl::Transform& scaleX(float val);
    cgl::Transform& scaleY(float val);
    cgl::Transform& scaleZ(float val);

    cgl::Transform& inverse();

    cgl::Transform& translate(const glm::vec3& pos);
    cgl::Transform& translate(float x, float y, float z);
    cgl::Transform& translateX(float val);
    cgl::Transform& translateY(float val);
    cgl::Transform& translateZ(float val);

    cgl::Transform& rotate(float angle, float x, float y, float z);
    cgl::Transform& rotateX(float angle);
    cgl::Transform& rotateY(float angle);
    cgl::Transform& rotateZ(float angle);

    static Transform makeOrtogonal(float left, float right, float bottom, float top, float near, float far);
    static Transform makePerspective(float fov, float ratio, float near, float far);

    void ortogonal(float left, float right, float bottom, float top, float near, float far);
    void perspective(float fov, float ratio, float near, float far);

    Transform operator*(const Transform& right) const;
    Transform& operator*=(const Transform& right);

    glm::mat4 data() const;

private:
    glm::mat4 m_matrix;
};
}
