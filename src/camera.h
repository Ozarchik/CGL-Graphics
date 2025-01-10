#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CGL {
class Camera {
public:
    Camera() = default;
    float x() const;
    float y() const;

    glm::vec3 pos() const;

    void move(glm::vec3 pos);
    void move(float x);
    void rotate(float x, float y);
    void move(float x, float y, float z);

    void stepUp();
    void stepDown();
    void stepFront();
    void stepBack();
    void stepLeft();
    void stepRight();

    glm::mat4 getLookAt();

private:
    float m_pitch, m_yaw, m_roll;
    float m_x, m_y;
    float m_sensvity = 0.1f;

    glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_speed = 0.05f;
};
};
