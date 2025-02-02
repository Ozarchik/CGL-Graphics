#include "normalmapexample.h"

NormalMapExample::NormalMapExample()
{
    // --- Screen shader ---

    // normalMap.use();

    // CGL::Transform rotMod;
    // view = camera.getLookAt();
    // brickShader.use();
    // model.reset();
    // // view = camera.getLookAt();
    // projection.reset();
    // projection.perspective(45.0f, window.width()/window.height(), 1.0f, 100.0f);

    // brickShader.setInt("brick", 0);
    // brickShader.setInt("brickNormal", 1);

    // brickShader.setVec3("lightPos", glm::vec3(0.5f, 1.0f, 0.3f));
    // brickShader.setVec3("viewPos", camera.pos());
    // brickShader.setMat4("model", model);
    // brickShader.setMat4("view", view);
    // brickShader.setMat4("projection", projection);
    // brickShader.setMat4("MVP", mvp);

    // glBindVertexArray(brickVAO);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, brickTexId);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, brickNormalTexId);
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    // cubeShader.use();
    // model.reset();
    // brickShader.setVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
    // brickShader.setMat4("model", model.data());
    // brickShader.setMat4("view", view.data());
    // brickShader.setMat4("projection", projection.data());
    // testCube->draw(cubeShader);

    // PART 2

    // glGenBuffers(1, &brickVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, brickVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(brickVertices), &brickVertices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // glGenBuffers(1, &brickNormalVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, brickNormalVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(brickNormals), &brickNormals, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // glGenBuffers(1, &brickTexVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, brickTexVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(brickTexes), &brickTexes, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));

    // glGenBuffers(1, &brickTangentVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, brickTangentVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(brickTangents), &brickTangents, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(3);
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));

    // glGenBuffers(1, &brickBitangentVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, brickBitangentVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(brickBitangents), &brickBitangents, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(4);
    // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
}
