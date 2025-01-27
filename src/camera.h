#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CGL {
class Camera {
public:
    Camera();
    float x() const;
    float y() const;

    void setPos(glm::vec3 pos);
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

    void update();

private:
    float m_pitch = 0.0f, m_yaw = 90.0f, m_roll = 0.0f;
    float m_x, m_y;
    float m_sensvity = 0.05f;

    glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);


    float m_speed = 0.01f;
};
}
