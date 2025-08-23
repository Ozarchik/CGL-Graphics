#include <cgl/core/transform.h>

CGL::Transform::Transform()
    : m_matrix(0.0f)
{
    reset();
}

CGL::Transform::Transform(const glm::mat4& mat)
    : m_matrix(mat)
{
}

CGL::Transform CGL::Transform::clone() const
{
    return CGL::Transform(m_matrix);
}

CGL::Transform &CGL::Transform::reset()
{
    m_matrix = glm::mat4(1.0f);
    return *this;
}

CGL::Transform& CGL::Transform::translate(const glm::vec3& pos)
{
    m_matrix = glm::translate(m_matrix, pos);
    return *this;
}

CGL::Transform& CGL::Transform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
    return *this;
}

CGL::Transform& CGL::Transform::translateX(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(val, 0.0, 0.0));
    return *this;
}

CGL::Transform& CGL::Transform::translateY(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, val, 0.0));
    return *this;
}

CGL::Transform& CGL::Transform::translateZ(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, 0.0, val));
    return *this;
}

CGL::Transform &CGL::Transform::inverse()
{
    m_matrix = glm::mat4(m_matrix);
    return *this;
}

CGL::Transform& CGL::Transform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
    return *this;
}

CGL::Transform& CGL::Transform::scale(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, val, val));
    return *this;
}

CGL::Transform& CGL::Transform::scaleX(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, 1.0, 1.0));
    return *this;
}

CGL::Transform& CGL::Transform::scaleY(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, val, 1.0));
    return *this;
}

CGL::Transform& CGL::Transform::scaleZ(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, 1.0, val));
    return *this;
}

CGL::Transform &CGL::Transform::rotate(float angle, float x, float y, float z)
{
    m_matrix = glm::rotate (
        m_matrix,
        glm::radians(angle),
        glm::vec3(x, y, z)                
    );

    return *this;
}

CGL::Transform &CGL::Transform::rotateX(float angle)
{
    return rotate(angle, 1, 0, 0);
}

CGL::Transform &CGL::Transform::rotateY(float angle)
{
    return rotate(angle, 0, 1, 0);
}

CGL::Transform &CGL::Transform::rotateZ(float angle)
{
    return rotate(angle, 0, 0, 1);
}

void CGL::Transform::ortogonal(float left, float right, float bottom, float top, float near, float far)
{
    *this = makeOrtogonal(left, right, bottom, top, near, far);
}

void CGL::Transform::perspective(float fov, float ration, float near, float far)
{
    *this = makePerspective(fov, ration, near, far);
}

CGL::Transform CGL::Transform::makeOrtogonal(float left, float right, float bottom, float top, float near, float far)
{
    CGL::Transform transform = CGL::Transform(glm::ortho(left, right, bottom, top, near, far));
    return transform;
}

CGL::Transform CGL::Transform::makePerspective(float fov, float ration, float near, float far)
{
    CGL::Transform transform = CGL::Transform(glm::perspective(
        glm::radians(fov), 
        ration,
        near,
        far
    ));

    return transform;
}

CGL::Transform CGL::Transform::operator*(const Transform &right) const
{
    glm::mat4 matrix = glm::mat4(m_matrix * right.m_matrix);
    return CGL::Transform(matrix);
}

CGL::Transform &CGL::Transform::operator*=(const Transform &right)
{
    m_matrix *= right.m_matrix;
    return *this;
}

glm::mat4 CGL::Transform::data() const
{
    return m_matrix;
}
