#include "light.h"

CGL::Light::Light(const glm::vec3& pos, const glm::vec3& color)
    : m_pos(pos), m_color(color)
{
}

void CGL::Light::setup(ShaderProgram& shaderProgram)
{
    shaderProgram.setVec3("lightPos", m_pos);
    shaderProgram.setVec3("lightColor", m_color);
}