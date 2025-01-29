#include "camera.h"
#include <iostream>


glm::mat4 CGL::Camera::getLookAt()
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

CGL::Camera::Camera()
{
    m_front = glm::vec3(0.0f, 0.0f, 1.0f);
    m_worldUp = m_up;

    update();
}

float CGL::Camera::x() const
{
    return m_x;
}

float CGL::Camera::y() const
{
    return m_y;
}

void CGL::Camera::setPos(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 CGL::Camera::pos() const
{
    return m_pos;
}

void CGL::Camera::rotate(float targX, float targY)
{
    static float lastX = targX;
    static float lastY = targY;

	float xoffset = targX - lastX;
    float yoffset = lastY - targY;

	lastX = targX;
	lastY = targY;

	xoffset *= m_sensvity;
	yoffset *= m_sensvity;

	m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f)  m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;

    update();
}

void CGL::Camera::update()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

void CGL::Camera::move(float x)
{

}

void CGL::Camera::move(float x, float y, float z)
{

}

void CGL::Camera::stepUp()
{
    m_pos += m_speed * m_up;
}

void CGL::Camera::stepDown()
{
    m_pos -= m_speed * m_up;
}

void CGL::Camera::stepFront()
{
    m_pos += m_speed * m_front;
}

void CGL::Camera::stepBack()
{
    m_pos -= m_speed * m_front;
}

void CGL::Camera::stepLeft()
{
    m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}

void CGL::Camera::stepRight()
{
    m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}
