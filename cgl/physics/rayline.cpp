#include <cgl/physics/rayline.h>
#include <cgl/managers/resourcemanager.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <glad/glad.h>
#include <iomanip>

GLuint VAO = 0, VBO = 0;

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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // m_vao = VAOBufferBuilder::build()
    //                       .setVertexData(line, sizeof(line), cgl::DrawChangeMode::Dynamic)
    //                       .setAttribute(0, 3, sizeof(glm::vec3), 0)
    //                       .done();
}

void cgl::RayLine::update(glm::vec3 origin, glm::vec3 direction, float length)
{
    // line[0] = origin;
    // line[1] = origin + direction * length;


    line[0] = glm::vec3(0);
    // line[0] = m_camera.pos();
    line[1] = glm::vec3(100, 100, 100);

    // m_vao->setVertexSubData(line, sizeof(line));
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_DYNAMIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    cglDebug() << "update";
}
#include <cgl/core/engine.h>
void cgl::RayLine::draw()
{
    m_shader->use();
    m_shader->setView(cglEngine().activeCamera()->getView());
    m_shader->setProjection(cglEngine().activeCamera()->getProjection());
    m_shader->setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));

    glLineWidth(20.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    // m_vao->bind();
    // cglRenderContext().render(PrimitiveData {cgl::Primitive::Line, cgl::DrawType::Elements, 2, 0});
    // m_vao->unbind();
    m_shader->done();
}
