#include <cgl/core/transform.h>

cgl::Transform::Transform()
    : m_matrix(0.0f)
{
    reset();
}

cgl::Transform::Transform(const glm::mat4& mat)
    : m_matrix(mat)
{
}

cgl::Transform cgl::Transform::clone() const
{
    return cgl::Transform(m_matrix);
}

cgl::Transform &cgl::Transform::reset()
{
    m_matrix = glm::mat4(1.0f);
    return *this;
}

cgl::Transform& cgl::Transform::translate(const glm::vec3& pos)
{
    m_matrix = glm::translate(m_matrix, pos);
    return *this;
}

cgl::Transform& cgl::Transform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
    return *this;
}

cgl::Transform& cgl::Transform::translateX(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(val, 0.0, 0.0));
    return *this;
}

cgl::Transform& cgl::Transform::translateY(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, val, 0.0));
    return *this;
}

cgl::Transform& cgl::Transform::translateZ(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, 0.0, val));
    return *this;
}

cgl::Transform &cgl::Transform::inverse()
{
    m_matrix = glm::mat4(m_matrix);
    return *this;
}

cgl::Transform& cgl::Transform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
    return *this;
}

cgl::Transform& cgl::Transform::scale(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, val, val));
    return *this;
}

cgl::Transform& cgl::Transform::scaleX(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, 1.0, 1.0));
    return *this;
}

cgl::Transform& cgl::Transform::scaleY(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, val, 1.0));
    return *this;
}

cgl::Transform& cgl::Transform::scaleZ(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, 1.0, val));
    return *this;
}

cgl::Transform &cgl::Transform::rotate(float angle, float x, float y, float z)
{
    m_matrix = glm::rotate (
        m_matrix,
        glm::radians(angle),
        glm::vec3(x, y, z)                
    );

    return *this;
}

cgl::Transform &cgl::Transform::rotateX(float angle)
{
    return rotate(angle, 1, 0, 0);
}

cgl::Transform &cgl::Transform::rotateY(float angle)
{
    return rotate(angle, 0, 1, 0);
}

cgl::Transform &cgl::Transform::rotateZ(float angle)
{
    return rotate(angle, 0, 0, 1);
}

void cgl::Transform::ortogonal(float left, float right, float bottom, float top, float near, float far)
{
    *this = makeOrtogonal(left, right, bottom, top, near, far);
}

void cgl::Transform::perspective(float fov, float ration, float near, float far)
{
    *this = makePerspective(fov, ration, near, far);
}

cgl::Transform cgl::Transform::makeOrtogonal(float left, float right, float bottom, float top, float near, float far)
{
    cgl::Transform transform = cgl::Transform(glm::ortho(left, right, bottom, top, near, far));
    return transform;
}

cgl::Transform cgl::Transform::makePerspective(float fov, float ration, float near, float far)
{
    cgl::Transform transform = cgl::Transform(glm::perspective(
        glm::radians(fov), 
        ration,
        near,
        far
    ));

    return transform;
}

cgl::Transform cgl::Transform::operator*(const Transform &right) const
{
    glm::mat4 matrix = glm::mat4(m_matrix * right.m_matrix);
    return cgl::Transform(matrix);
}

cgl::Transform &cgl::Transform::operator*=(const Transform &right)
{
    m_matrix *= right.m_matrix;
    return *this;
}

glm::mat4 cgl::Transform::data() const
{
    return m_matrix;
}
