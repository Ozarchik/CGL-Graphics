#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cmath>

#include "buffer.h"
#include "camera.h"
#include "cube.h"
#include "sphere.h"
#include "light.h"
#include "texture.h"
#include "transform.h"
#include "model.h"
#include "scene.h"
#include "shader.h"
#include "window.h"
#include "inputcontroller.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

CGL::Window window;
CGL::Camera camera;

CGL::Shader modelShader;
CGL::Shader lightShader;
CGL::Shader cubeShader;
CGL::Shader skyboxShader;
CGL::Shader brickShader;
CGL::Scene scene;

CGL::Cube* lightCube;

unsigned int brickTexId;
unsigned int brickNormalTexId;
unsigned int brickVBO;
unsigned int brickNormalVBO;
unsigned int brickTexVBO;
unsigned int brickTangentVBO;
unsigned int brickBitangentVBO;
unsigned int brickVAO;

unsigned int cubeMapId;
unsigned int cubemapVBO;
unsigned int cubemapVAO;

std::vector<CGL::Light> lights {
    {
        glm::vec3(0.0f, 2.5f, 2.5f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    },
    {
        glm::vec3(0.0f, -2.5f, -2.5f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    },
    {
        glm::vec3(2.5f, 2.5f, 5.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    },
};

float m_brickSize = 5.0f;

float brickVertices[] = {
    -m_brickSize/2,  m_brickSize/2, 0.0,
     m_brickSize/2,  m_brickSize/2, 0.0,
     m_brickSize/2, -m_brickSize/2, 0.0,

    -m_brickSize/2,  m_brickSize/2, 0.0,
     m_brickSize/2, -m_brickSize/2, 0.0,
    -m_brickSize/2, -m_brickSize/2, 0.0,
};

float brickTexes[] = {
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0,

    0.0, 1.0,
    1.0, 0.0,
    0.0, 0.0
};


float m_skySize = 100.0f;

float skyboxVertices[] = {
    // positions
    -m_skySize,  m_skySize, -m_skySize,
    -m_skySize, -m_skySize, -m_skySize,
     m_skySize, -m_skySize, -m_skySize,
     m_skySize, -m_skySize, -m_skySize,
     m_skySize,  m_skySize, -m_skySize,
    -m_skySize,  m_skySize, -m_skySize,

    -m_skySize, -m_skySize,  m_skySize,
    -m_skySize, -m_skySize, -m_skySize,
    -m_skySize,  m_skySize, -m_skySize,
    -m_skySize,  m_skySize, -m_skySize,
    -m_skySize,  m_skySize,  m_skySize,
    -m_skySize, -m_skySize,  m_skySize,

     m_skySize, -m_skySize, -m_skySize,
     m_skySize, -m_skySize,  m_skySize,
     m_skySize,  m_skySize,  m_skySize,
     m_skySize,  m_skySize,  m_skySize,
     m_skySize,  m_skySize, -m_skySize,
     m_skySize, -m_skySize, -m_skySize,

    -m_skySize, -m_skySize,  m_skySize,
    -m_skySize,  m_skySize,  m_skySize,
     m_skySize,  m_skySize,  m_skySize,
     m_skySize,  m_skySize,  m_skySize,
     m_skySize, -m_skySize,  m_skySize,
    -m_skySize, -m_skySize,  m_skySize,

    -m_skySize,  m_skySize, -m_skySize,
     m_skySize,  m_skySize, -m_skySize,
     m_skySize,  m_skySize,  m_skySize,
     m_skySize,  m_skySize,  m_skySize,
    -m_skySize,  m_skySize,  m_skySize,
    -m_skySize,  m_skySize, -m_skySize,

    -m_skySize, -m_skySize, -m_skySize,
    -m_skySize, -m_skySize,  m_skySize,
     m_skySize, -m_skySize, -m_skySize,
     m_skySize, -m_skySize, -m_skySize,
    -m_skySize, -m_skySize,  m_skySize,
     m_skySize, -m_skySize,  m_skySize
};

void initOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		std::abort();
	}

	glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window.getWindow(), framebufferSizeCallback);

    glViewport(0, 0, window.width(), window.height());
}

int loop() {					
    CGL::Model renderModel("C:/MyCode/CGL-Graphics/assets/backpack/backpack.obj", false);
    // CGL::Model bedModel("C:/MyCode/CGL-Graphics/assets/furniture-pack-3d-model/OBJ/BookCaseLarge.obj", true);
    // CGL::Model samuraiModel("C:/MyCode/CGL-Graphics/assets/-samurai-3d-model/Samurai_Attack-bl.obj", false);
    CGL::Model chairModel("C:/MyCode/CGL-Graphics/assets/chair/eggchair.obj", true);

    // CGL::Model renderModel("assets/backpack/backpack.obj");
	// CGL::Model renderModel("src/InteriorTest.fbx");

    CGL::InputController inputController(&window, &camera);
    camera.setPos({-2.5f, 2.5f, -5.0f});
    auto testCube = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f));


    while (!glfwWindowShouldClose(window.getWindow())) {

        inputController.process();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double timeVal = glfwGetTime() * 60;

        cubeShader.use();

		CGL::Transform view = camera.getLookAt();
        cubeShader.setMat4("view", view);

		CGL::Transform projection;
        projection.perspective(45.0f, window.width()/window.height(), 1.0f, 100.0f);
        cubeShader.setMat4("projection", projection);

		CGL::Transform model;

		// model.rotate(90.0f, 1.0f, 1.0f, 0.0f);
        cubeShader.setMat4("model", model);
        model.translate(0.0f, 0.0f, 5.0f);

        cubeShader.setVec3("viewPos", camera.pos());

        // cubeShader.setVec3("light.position", glm::vec3(0.0f, 0.0f, 5.0f));
        // cubeShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);

        cubeShader.setVec3("lights[0].position", lights[0].pos);
        cubeShader.setVec3("lights[0].color", lights[0].color);

        cubeShader.setVec3("lights[1].position", lights[1].pos);
        cubeShader.setVec3("lights[1].color", lights[1].color);

        cubeShader.setVec3("lights[2].position", lights[2].pos);
        cubeShader.setVec3("lights[2].color", lights[2].color);

        cubeShader.setInt("material.diffuse", 0);
        cubeShader.setInt("material.specular", 1);
        // cubeShader.setVec3("material.ambient", 0.1f, 0.1f, 0.1f);
        // cubeShader.setVec3("material.diffuse", 0.0f, 0.0f, 0.5f);
        // cubeShader.setVec3("material.specular", 1.0f, 0.0f, 0.0f);
        cubeShader.setFloat("material.shininess", 252.0f);

        cubeShader.setVec3("viewDir", camera.pos());

        int count = 1;
        for (int i = 0; i < scene.meshes().size()/2; i++) {
            CGL::Transform rotMod = model;
            rotMod.rotate(count++ * 45.0f + timeVal, 0.0f, 0.0f, 1.0f);
            rotMod.translate(5.0f, 0.0f, 0.0f);

            cubeShader.setMat4("model", rotMod);
            cubeShader.use();
            auto m = scene.meshes()[i];
            // m->draw(cubeShader);
        }

        count = 1;
        for (int i = scene.meshes().size()/2 - 1; i < scene.meshes().size(); i++) {
            CGL::Transform rotMod = model;
            rotMod.rotate(count++ * 45.0f + timeVal, 1.0f, 0.0f, 0.0f);
            rotMod.translate(0.0f, 10.0f, 0.0f);

            cubeShader.setMat4("model", rotMod);
            cubeShader.use();
            auto m = scene.meshes()[i];
            // m->draw(cubeShader);
        }

        // --- Light shader ---

        lightShader.use();
        model.reset();

        CGL::Transform mvp = projection * view * model;
        lightShader.setMat4("MVP", mvp);
        // lightCube->draw(lightShader);

        // --- Normal map ----

        // CGL::Transform rotMod;
        // view = camera.getLookAt();
        brickShader.use();
        model.reset();
        // view = camera.getLookAt();
        projection.reset();
        projection.perspective(45.0f, window.width()/window.height(), 1.0f, 100.0f);

        brickShader.setInt("brick", 0);
        brickShader.setInt("brickNormal", 1);

        brickShader.setVec3("lightPos", glm::vec3(0.5f, 1.0f, 0.3f));
        brickShader.setVec3("viewPos", camera.pos());
        model = glm::rotate(model.data(), glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(0.0, 0.0, 1.0)));
        brickShader.setMat4("model", model);
        brickShader.setMat4("view", view);
        brickShader.setMat4("projection", projection);
        // brickShader.setMat4("MVP", mvp);

        glBindVertexArray(brickVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, brickTexId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, brickNormalTexId);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // cubeShader.use();
        // model.reset();
        // brickShader.setVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
        // brickShader.setMat4("model", model.data());
        // brickShader.setMat4("view", view.data());
        // brickShader.setMat4("projection", projection.data());
        // testCube->draw(cubeShader);

        // --- Skybox ---

        // glDepthFunc(GL_LEQUAL);

        // skyboxShader.use();
        // glm::mat4 viewMat = glm::mat4(glm::mat3(camera.getLookAt()));
        // skyboxShader.setMat4("view", viewMat);
        // skyboxShader.setMat4("projection", projection.data());
        // skyboxShader.setInt("skybox", 0);
        // glBindVertexArray(cubemapVAO);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapId);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // glDepthFunc(GL_LESS);

        // glBindVertexArray(0);

        // --- Model shader ---

        // modelShader.use();

        // modelShader.setMat4("model", model.data());
        // modelShader.setMat4("view", view.data());
        // modelShader.setMat4("projection", projection.data());
        // model.reset();
        // model.translate(0.0f, 0.0f, -5.0f);
        // mvp = projection * view * model;
        // modelShader.setMat4("MVP", mvp);

        // renderModel.draw(modelShader);

        // model.reset();
        // model.translate(5.0f, 0.0f, 0.0f);

        // modelShader.setMat4("model", model.data());
        // bedModel.draw(modelShader);

        // model.reset();
        // model.scale(10.0f, 10.0f, 10.0f);
        // mvp = projection * view * model;
        // modelShader.setMat4("MVP", mvp);
        // chairModel.draw(modelShader);
        // samuraiModel.draw(modelShader);

        window.update();
	}

	return 0;
}

int main()
{
    window.init();
	initOpenGL();

    std::vector<TextureBase> cubeTexes {
        TextureBase::create("textures/container/container.png", "diffuse"),
        TextureBase::create("textures/container/container_border.png", "specular")
    };

    // Skybox [begin]

    cubeMapId = TextureBase::loadCubmap(
        "textures/skybox",
        {
            "right.jpg", "left.jpg",
            "top.jpg", "bottom.jpg",
            "front.jpg", "back.jpg"
        }
    );

    glGenVertexArrays(1, &cubemapVAO);
    glBindVertexArray(cubemapVAO);

    glGenBuffers(1, &cubemapVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubemapVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Brick

    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);



    float quadVertices[] = {
        // positions            // normal         // texcoords  // tangent                          // bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };

    // float brickNormals[] = {
    //     0.0, 1.0,
    //     1.0, 1.0,
    //     1.0, 0.0,

    //     0.0, 1.0,
    //     1.0, 0.0,
    //     0.0, 0.0
    // };


    // float brickTangents[] = {
    //     0.0, 1.0,
    //     1.0, 1.0,
    //     1.0, 0.0,

    //     0.0, 1.0,
    //     1.0, 0.0,
    //     0.0, 0.0
    // };

    // float brickBitangents[] = {
    //     0.0, 1.0,
    //     1.0, 1.0,
    //     1.0, 0.0,

    //     0.0, 1.0,
    //     1.0, 0.0,
    //     0.0, 0.0
    // };

    // ---------------------

    brickTexId = TextureBase::loadFromFile("textures/brick/brick.jpg");
    brickNormalTexId = TextureBase::loadFromFile("textures/brick/brick_normal.jpg");

    glGenVertexArrays(1, &brickVAO);
    glBindVertexArray(brickVAO);

    glGenBuffers(1, &brickVBO);
    glBindBuffer(GL_ARRAY_BUFFER, brickVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

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

    glBindVertexArray(0);


    // Skybox [end]

    // CGL::Cube* cube1 = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f), cubeTexes);
    // CGL::Cube* cube2 = new CGL::Cube(glm::vec3(5.0f, 0.0f, 0.0f), cubeTexes);
    // CGL::Cube* cube3 = new CGL::Cube(glm::vec3(0.0f, 0.0f, -5.0f), cubeTexes);
    // CGL::Cube* cube4 = new CGL::Cube(glm::vec3(-5.0f, 0.0f, 0.0f), cubeTexes);

    for (int i = 0; i < 16; i++) {
        CGL::Cube* cube = new CGL::Cube;
        scene.addMesh(cube);
    }

    // for (int i = 0; i < 16; i++) {
    //     CGL::Sphere* sphere = new CGL::Sphere();
    //     scene.addMesh(sphere);
    // }
    lightCube = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f));

    // scene.addMesh(cube1);
    // scene.addMesh(cube2);
    // scene.addMesh(cube3);
    // scene.addMesh(cube4);
    // scene.addMesh(sphere);

    cubeShader   = CGL::Shader("shaders/cube.vert",  "shaders/cube.frag");
    lightShader  = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    modelShader  = CGL::Shader("shaders/model.vert", "shaders/model.frag");
    skyboxShader = CGL::Shader("shaders/skybox.vert", "shaders/skybox.frag");
    brickShader  = CGL::Shader("shaders/brick.vert", "shaders/brick.frag");

	return loop();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
