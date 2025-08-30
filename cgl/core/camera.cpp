#include <cgl/core/camera.h>
#include <iostream>

cgl::Camera::Camera()
    : m_fov(45.0)
{
    // m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_worldUp = m_up;

    updateInternal();
}

float cgl::Camera::fov() const
{
    return m_fov;
}

void cgl::Camera::setFov(float fov)
{
    m_fov = fov;
}

glm::mat4 cgl::Camera::getLookAt() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

cgl::Transform cgl::Camera::getView()
{
    return cgl::Transform(getLookAt());
}

cgl::Transform cgl::Camera::getProjection()
{
    return cgl::Transform::makePerspective(m_fov, cglCoreContext().aspect(), 0.1f, 100.0f);
}

void cgl::Camera::correctSpeed(float coeff)
{
    m_deltaTime = coeff;
}

void cgl::Camera::setSpeed(float speed)
{
    m_speed = speed;
}

float cgl::Camera::speed() const
{
    return m_speed;
}

void cgl::Camera::update()
{
    correctSpeed(cglCoreContext().deltaTime());
}

void cgl::Camera::setPos(glm::vec3 pos)
{
    m_pos = pos;
}

glm::vec3 cgl::Camera::pos() const
{
    return m_pos;
}

void cgl::Camera::rotate(float targX, float targY)
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

void cgl::Camera::updateInternal()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}

void cgl::Camera::keyEventHandler(const KeyEvent& event)
{
    switch (event.type()) {
    case cgl::Key_A: {
        stepLeft();
    } break;
    case cgl::Key_B: {
        m_rotateMode = !m_rotateMode;
    } break;
    case cgl::Key_D: {
        stepRight();
    } break;
    case cgl::Key_Q: {
        rotateLeft();
    } break;
    case cgl::Key_E: {
        rotateRight();
    } break;
    case cgl::Key_S: {
        stepBack();
    } break;
    case cgl::Key_W: {
        stepForward();
    } break;
    case cgl::Key_C: {
        stepUp();
    } break;
    case cgl::Key_Z: {
        stepDown();
    } break;
    case cgl::Key_Space: {
        stepUp();
    } break;
    }
}

void cgl::Camera::mouseWheelEventHandler(const MouseWheelEvent &event)
{
    if (event.direction() == cgl::MouseWheelDirection::Up)
        zoomUp();
    if (event.direction() == cgl::MouseWheelDirection::Down)
        zoomDown();
}

void cgl::Camera::mouseEventHandler(const MouseEvent &event)
{
    rotate(event.x(), event.y());
}

void cgl::Camera::move(float x)
{

}

void cgl::Camera::move(float x, float y, float z)
{

}

void cgl::Camera::zoomUp()
{
    m_pos += 100.0f*m_speed * m_front* m_deltaTime;
}

void cgl::Camera::zoomDown()
{
    m_pos -= 100.0f*m_speed * m_front* m_deltaTime;
}

void cgl::Camera::stepUp()
{
    m_pos += m_speed * m_up * m_deltaTime;
}

void cgl::Camera::stepDown()
{
    m_pos -= m_speed * m_up * m_deltaTime;
}

void cgl::Camera::stepForward()
{
    m_pos += m_speed * m_front * m_deltaTime;
}

void cgl::Camera::stepBack()
{
    m_pos -= m_speed * m_front * m_deltaTime;
}

void cgl::Camera::stepLeft()
{
    m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * m_deltaTime;
}

void cgl::Camera::stepRight()
{
    m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed * m_deltaTime;
}

void cgl::Camera::rotateLeft()
{
    rotate(lastX - 1.0, lastY);
}

void cgl::Camera::rotateRight()
{
    rotate(lastX + 1.0, lastY);
}

glm::vec3 cgl::Camera::front() const
{
    return m_front;
}
