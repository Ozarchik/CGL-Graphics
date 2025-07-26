#include <examples/skybox.h>

SkyBox::SkyBox()
{
    // --- Skybox ---



    // float m_skySize = 1.0f;

    // float skyboxVertices[] = {
    //     // positions
    //     -m_skySize,  m_skySize, -m_skySize,
    //     -m_skySize, -m_skySize, -m_skySize,
    //      m_skySize, -m_skySize, -m_skySize,
    //      m_skySize, -m_skySize, -m_skySize,
    //      m_skySize,  m_skySize, -m_skySize,
    //     -m_skySize,  m_skySize, -m_skySize,

    //     -m_skySize, -m_skySize,  m_skySize,
    //     -m_skySize, -m_skySize, -m_skySize,
    //     -m_skySize,  m_skySize, -m_skySize,
    //     -m_skySize,  m_skySize, -m_skySize,
    //     -m_skySize,  m_skySize,  m_skySize,
    //     -m_skySize, -m_skySize,  m_skySize,

    //      m_skySize, -m_skySize, -m_skySize,
    //      m_skySize, -m_skySize,  m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //      m_skySize,  m_skySize, -m_skySize,
    //      m_skySize, -m_skySize, -m_skySize,

    //     -m_skySize, -m_skySize,  m_skySize,
    //     -m_skySize,  m_skySize,  m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //      m_skySize, -m_skySize,  m_skySize,
    //     -m_skySize, -m_skySize,  m_skySize,

    //     -m_skySize,  m_skySize, -m_skySize,
    //      m_skySize,  m_skySize, -m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //      m_skySize,  m_skySize,  m_skySize,
    //     -m_skySize,  m_skySize,  m_skySize,
    //     -m_skySize,  m_skySize, -m_skySize,

    //     -m_skySize, -m_skySize, -m_skySize,
    //     -m_skySize, -m_skySize,  m_skySize,
    //      m_skySize, -m_skySize, -m_skySize,
    //      m_skySize, -m_skySize, -m_skySize,
    //     -m_skySize, -m_skySize,  m_skySize,
    //      m_skySize, -m_skySize,  m_skySize
    // };


    // skyboxShader = CGL::Shader("shaders/skybox.vert", "shaders/skybox.frag");

    // unsigned int cubeMapId;
    // unsigned int cubemapVBO;
    // unsigned int cubemapVAO;

    // glDepthFunc(GL_LEQUAL);
    // skyboxShader.use();
    // glm::mat4 viewMat = glm::mat4(glm::mat3(camera.getLookAt()));

    // skyboxShader.setMat4("model", model);
    // skyboxShader.setMat4("view", viewMat);
    // skyboxShader.setMat4("projection", projection);
    // skyboxShader.setInt("skybox", 0);
    // glBindVertexArray(cubemapVAO);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapId);
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    // glBindVertexArray(0);
    // glDepthFunc(GL_LESS);



    // -- continue --

    // std::vector<CGL::TextureBase> cubeTexes {
    //     CGL::TextureBase::create("textures/container/container.png", "diffuse"),
    //     CGL::TextureBase::create("textures/container/container_border.png", "specular")
    // };

    // Skybox [begin]

    // cubeMapId = CGL::TextureBase::loadCubmap(
    //     "textures/skybox",
    //     {
    //         "right.jpg", "left.jpg",
    //         "top.jpg", "bottom.jpg",
    //         "front.jpg", "back.jpg"
    //     }
    // );

    // glGenVertexArrays(1, &cubemapVAO);
    // glBindVertexArray(cubemapVAO);

    // glGenBuffers(1, &cubemapVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, cubemapVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


}
