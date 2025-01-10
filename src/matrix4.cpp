#include "matrix4.h"

CGL::Matrix4::Matrix4()
{
    m_matrix = glm::mat4(1.0f);
}

CGL::Matrix4::Matrix4(const glm::mat4& mat)
{
    m_matrix = mat;
}

void CGL::Matrix4::translate(float x, float y, float z)
{
    m_matrix = glm::translate (
        m_matrix,
        glm::vec3(x, y, z)
    );
}

void CGL::Matrix4::scale(float x, float y, float z)
{
    m_matrix = glm::scale (
        m_matrix,
        glm::vec3(x, y, z)
    );
}

void CGL::Matrix4::rotate(float angle, float x, float y, float z)
{
    m_matrix = glm::rotate (
        m_matrix,
        glm::radians(angle),
        glm::vec3(x, y, z)                
    );
}

void CGL::Matrix4::perspective(float fov, float ration, float near, float far)
{
    m_matrix = glm::perspective(
        glm::radians(fov),
        ration,
        near,
        far
    );
}

glm::mat4 CGL::Matrix4::data() const
{
    return m_matrix;
}