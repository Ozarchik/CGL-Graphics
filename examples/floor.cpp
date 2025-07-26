#include <examples/floor.h>
#include <glad/glad.h>
#include <cgl/texture/texturebase.h>
#include <cgl/texture/textureloader.h>

CGL::Floor::Floor()
{
    m_shader = CGL::Shader("shaders/floor.vert", "shaders/floor.frag");

    float floorVertices[] = {
        -1.0, 0.0, 1.0, 0.0, 1.0,
        -1.0, 0.0, 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0, 1.0, 0.0,

        1.0, 0.0, 0.0, 1.0, 0.0,
        1.0, 0.0, 1, 1.0, 1.0,
        -1.0, 0.0, 1.0, 0.0, 1.0
    };

    int rows = 10, cols = 10;
    unsigned char floorTexture[rows*cols*4] {0};

    for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 2) {

            int index = 4*(i*cols + j + i % 2);
            floorTexture[index]   = 255;
            floorTexture[index+1] = 0;
            floorTexture[index+2] = 0;
            floorTexture[index+3] = 0;
        }
    }

    glGenBuffers(1, &floorVBO);
    glGenVertexArrays(1, &floorVAO);
    glBindVertexArray(floorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), &floorVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glBindVertexArray(0);

    glGenTextures(1, &floorTex);
    glBindTexture(GL_TEXTURE_2D, floorTex);
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rows, cols, 0, GL_RGBA, GL_UNSIGNED_BYTE, floorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    brickTex = CGL::TextureLoader::loadFromFile("textures/brick/brick.jpg").id;
}

void CGL::Floor::use(const CGL::Window& window, const CGL::Camera& camera)
{
    m_shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, brickTex);

    glBindVertexArray(floorVAO);

    CGL::Transform model;
    CGL::Transform view = camera.getLookAt();
    CGL::Transform projection = glm::perspective(glm::radians(45.0f), window.aspect(), 1.0f, 100.0f);

    auto primType = GL_TRIANGLES; //GL_POINTS;

    model.translateY(1);
    model.translateZ(-50);
    model.rotate(120, 1, 0, 0);
    model.scale(10);
    static int count = 0;
    count++;
    model.rotate(count/15.0, 0.0, 0.0, 1);
    CGL::Transform mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);
    m_shader.setInt("floorTexture", 0);
    m_shader.setInt("brickTexture", 1);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(primType, 0, 6);

    model.rotate(45, 0.0, 0.0, 1);
    mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);

    glDrawArrays(primType, 0, 6);

    model.rotate(45, 0.0, 0.0, 1);
    mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);

    glDrawArrays(primType, 0, 6);

    model.rotate(45, 0.0, 0.0, 1);
    mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);

    glDrawArrays(primType, 0, 6);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
