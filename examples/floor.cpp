#include "floor.h"
#include "glad/glad.h"

CGL::Floor::Floor()
{
    float floorVertices[] = {
        -10.0, 0.0, 10.0, 0.0, 1.0,
        -10.0, 0.0, 0.0, 0.0, 0.0,
         10.0, 0.0, 0.0, 1.0, 0.0,

        10.0, 0.0, 0.0, 1.0, 0.0,
        10.0, 0.0, 10.0, 1.0, 1.0,
        -10.0, 0.0, 10.0, 0.0, 1.0
    };

    int rows = 15, cols = 15;
    unsigned char floorTexture[rows*cols*3] {0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            int index = ((rows - 1 - j) * cols + i) * 3;
            static bool even = false;
            even = !even;
            floorTexture[index]   = even ? 255 : 0;
            floorTexture[index+1] = even ? 255 : 0;
            floorTexture[index+2] = even ? 255 : 0;
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
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rows, cols, 0, GL_RGB, GL_UNSIGNED_BYTE, floorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glGenerateMipmap(GL_TEXTURE_2D);
}

void CGL::Floor::use(const CGL::Window& window, const CGL::Camera& camera)
{
    m_shader.use();
    glBindVertexArray(floorVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTex);

    CGL::Transform model;
    CGL::Transform view = camera.getLookAt();
    CGL::Transform projection = glm::perspective(glm::radians(45.0f), window.aspect(), 1.0f, 100.0f);;

    CGL::Transform mvp = projection * view * model;
    m_shader.setMat4("MVP", mvp);
    m_shader.setInt("floorTexture", 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
