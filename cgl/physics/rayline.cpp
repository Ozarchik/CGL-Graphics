#include <cgl/physics/rayline.h>
#include <cgl/managers/resourcemanager.h>
#include <glad/glad.h>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    os << std::fixed << std::setprecision(1) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

cgl::RayLine::RayLine(cgl::Camera &camera)
    : m_camera(camera)
{
    m_shader = cgl::ResourceManager::loadShader("rayline");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0);
}

void cgl::RayLine::update(glm::vec3 origin, glm::vec3 direction, float length)
{
    line[0] = origin;
    line[1] = origin + direction * length;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
}

void cgl::RayLine::draw()
{
    m_shader->use();
    m_shader->setMat4("view", m_camera.getView());
    m_shader->setMat4("projection", m_camera.getProjection());
    m_shader->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}
