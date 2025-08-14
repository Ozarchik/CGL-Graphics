#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cgl/event/event.h>
#include <cgl/object.h>
#include <cgl/corecontext.h>
#include <cgl/transform.h>

namespace CGL {
class Camera: public CGL::Object {
public:
    Camera(CGL::CoreContext& context);

    void setFov(float fov);
    float fov() const;

    void setPos(glm::vec3 pos);
    glm::vec3 pos() const;

    void move(glm::vec3 pos);
    void move(float x);
    void rotate(float x, float y);
    void move(float x, float y, float z);

    void zoomUp();
    void zoomDown();
    void stepUp();
    void stepDown();
    void stepForward();
    void stepBack();
    void stepLeft();
    void stepRight();
    void rotateLeft();
    void rotateRight();

    glm::vec3 front() const;
    glm::mat4 getLookAt() const;

    CGL::Transform getView();
    CGL::Transform getProjection();

    void correctSpeed(float coeff);
    void setSpeed(float speed);
    float speed() const;

    void update();

    void keyEventHandler(const KeyEvent &event) override;
    void mouseWheelEventHandler(const MouseWheelEvent &event) override;
    void mouseEventHandler(const MouseEvent &event) override;

private:
    void updateInternal();

private:
    float m_fov;
    float m_pitch = 0.0f, m_yaw = -90.0f, m_roll = 0.0f;
    float m_sensvity = 0.05f;

    glm::vec3 m_pos = glm::vec3(0.0f, 2.0f, 15.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);

    float m_distance = 15.0f;
    glm::vec3 m_target = glm::vec3(0.0f);

    float lastX = 0.0f;
    float lastY = 0.0f;
    float m_deltaTime = 0.0f;
    float m_speed = 5.5f;

    bool m_rotateMode = true;
    CGL::CoreContext& m_context;
};
}
