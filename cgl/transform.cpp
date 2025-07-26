#include <cgl/transform.h>

CGL::Transform::Transform()
{
    reset();
}

CGL::Transform::Transform(const glm::mat4& mat)
{
    m_matrix = mat;
}

void CGL::Transform::reset()
{
    m_matrix = glm::mat4(1.0f);
}

void CGL::Transform::translate(const glm::vec3& pos)
{
    m_matrix = glm::translate(m_matrix, pos);
}

void CGL::Transform::translate(float x, float y, float z)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(x, y, z));
}

void CGL::Transform::translateX(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(val, 0.0, 0.0));
}

void CGL::Transform::translateZ(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, 0.0, val));
}

void CGL::Transform::translateY(float val)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(0.0, val, 0.0));
}

void CGL::Transform::scale(float x, float y, float z)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(x, y, z));
}

void CGL::Transform::scale(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, val, val));
}

void CGL::Transform::scaleX(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(val, 1.0, 1.0));
}

void CGL::Transform::scaleY(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, val, 1.0));
}

void CGL::Transform::scaleZ(float val)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(1.0, 1.0, val));
}

void CGL::Transform::rotate(float angle, float x, float y, float z)
{
    m_matrix = glm::rotate (
        m_matrix,
        glm::radians(angle),
        glm::vec3(x, y, z)                
    );
}

void CGL::Transform::ortogonal(float left, float right, float bottom, float top, float near, float far)
{
    m_matrix = glm::ortho(left, right, bottom, top, near, far);
}

void CGL::Transform::perspective(float fov, float ration, float near, float far)
{
    m_matrix = glm::perspective(
        glm::radians(fov),
        ration,
        near,
        far
    );
}

CGL::Transform CGL::Transform::operator*(const Transform &right) const
{
    auto matrix = m_matrix * right.m_matrix;
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
