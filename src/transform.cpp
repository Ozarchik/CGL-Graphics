#include "transform.h"

CGL::Transform::Transform()
{
    m_matrix = glm::mat4(1.0f);
}

CGL::Transform::Transform(const glm::mat4& mat)
{
    m_matrix = mat;
}

void CGL::Transform::translate(float x, float y, float z)
{
    m_matrix = glm::translate (
        m_matrix,
        glm::vec3(x, y, z)
    );
}

void CGL::Transform::scale(float x, float y, float z)
{
    m_matrix = glm::scale (
        m_matrix,
        glm::vec3(x, y, z)
    );
}

void CGL::Transform::rotate(float angle, float x, float y, float z)
{
    m_matrix = glm::rotate (
        m_matrix,
        glm::radians(angle),
        glm::vec3(x, y, z)                
    );
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

glm::mat4 CGL::Transform::data() const
{
    return m_matrix;
}
