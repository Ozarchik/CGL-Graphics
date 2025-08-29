#include <cgl/core/camera.h>
#include <iostream>

CGL::Camera::Camera()
    : m_fov(45.0)
{
    // m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_worldUp = m_up;

    updateInternal();
}

float CGL::Camera::fov() const
{
    return m_fov;
}

void CGL::Camera::setFov(float fov)
{
    m_fov = fov;
}

glm::mat4 CGL::Camera::getLookAt() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

CGL::Transform CGL::Camera::getView()
{
    return CGL::Transform(getLookAt());
}

CGL::Transform CGL::Camera::getProjection()
{
    return CGL::Transform::makePerspective(m_fov, cglCoreContext().aspect(), 0.1f, 100.0f);
}

void CGL::Camera::correctSpeed(float coeff)
{
    m_deltaTime = coeff;
}

void CGL::Camera::setSpeed(float speed)
{
    m_speed = speed;
}

float CGL::Camera::speed() const
{
    return m_speed;
}

void CGL::Camera::update()
{
    correctSpeed(cglCoreContext().deltaTime());
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
	float xoffset = targX - lastX;
    float yoffset = lastY - targY;

	lastX = targX;
	lastY = targY;

    if (!m_rotateMode)
        return;

	xoffset *= m_sensvity;
	yoffset *= m_sensvity;

	m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f)  m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;

    updateInternal();
}

void CGL::Camera::updateInternal()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

void CGL::Camera::keyEventHandler(const KeyEvent& event)
{
    switch (event.type()) {
    case CGL::Key_A: {
        stepLeft();
    } break;
    case CGL::Key_B: {
        m_rotateMode = !m_rotateMode;
    } break;
    case CGL::Key_D: {
        stepRight();
    } break;
    case CGL::Key_Q: {
        rotateLeft();
    } break;
    case CGL::Key_E: {
        rotateRight();
    } break;
    case CGL::Key_S: {
        stepBack();
    } break;
    case CGL::Key_W: {
        stepForward();
    } break;
    case CGL::Key_C: {
        stepUp();
    } break;
    case CGL::Key_Z: {
        stepDown();
    } break;
    case CGL::Key_Space: {
        stepUp();
    } break;
    }
}

void CGL::Camera::mouseWheelEventHandler(const MouseWheelEvent &event)
{
    if (event.direction() == CGL::MouseWheelDirection::Up)
        zoomUp();
    if (event.direction() == CGL::MouseWheelDirection::Down)
        zoomDown();
}

void CGL::Camera::mouseEventHandler(const MouseEvent &event)
{
    rotate(event.x(), event.y());
}

void CGL::Camera::move(float x)
{

}

void CGL::Camera::move(float x, float y, float z)
{

}

void CGL::Camera::zoomUp()
{
    m_pos += 100.0f*m_speed * m_front* m_deltaTime;
}

void CGL::Camera::zoomDown()
{
    m_pos -= 100.0f*m_speed * m_front* m_deltaTime;
}

void CGL::Camera::stepUp()
{
    m_pos += m_speed * m_up * m_deltaTime;
}

void CGL::Camera::stepDown()
{
    m_pos -= m_speed * m_up * m_deltaTime;
}

void CGL::Camera::stepForward()
{
    m_pos += m_speed * m_front * m_deltaTime;
}

void CGL::Camera::stepBack()
{
    m_pos -= m_speed * m_front * m_deltaTime;
}

void CGL::Camera::stepLeft()
{
    m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * m_deltaTime;
}

void CGL::Camera::stepRight()
{
    m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed * m_deltaTime;
}

void CGL::Camera::rotateLeft()
{
    rotate(lastX - 1.0, lastY);
}

void CGL::Camera::rotateRight()
{
    rotate(lastX + 1.0, lastY);
}

glm::vec3 CGL::Camera::front() const
{
    return m_front;
}
