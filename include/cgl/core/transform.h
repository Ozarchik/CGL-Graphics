#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CGL {

class Transform {
public:
    Transform();
    Transform(const glm::mat4& mat);

    CGL::Transform clone() const;

    CGL::Transform& reset();
    CGL::Transform& scale(float val);
    CGL::Transform& scale(float x, float y, float z);
    CGL::Transform& scaleX(float val);
    CGL::Transform& scaleY(float val);
    CGL::Transform& scaleZ(float val);

    CGL::Transform& inverse();

    CGL::Transform& translate(const glm::vec3& pos);
    CGL::Transform& translate(float x, float y, float z);
    CGL::Transform& translateX(float val);
    CGL::Transform& translateY(float val);
    CGL::Transform& translateZ(float val);

    CGL::Transform& rotate(float angle, float x, float y, float z);
    CGL::Transform& rotateX(float angle);
    CGL::Transform& rotateY(float angle);
    CGL::Transform& rotateZ(float angle);

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
