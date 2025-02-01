#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cmath>

// examples
#include "blend.h"
#include "cullface.h"


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
#include "normalmap.h"
#include "framebuffer.h"
#include "shadowmap.h"
#include "vertexbuffer.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

CGL::Window window;
CGL::Camera camera;

CGL::Shader modelShader;
CGL::Shader lightShader;
CGL::Shader cubeShader;
CGL::Shader stencilShader;
CGL::Shader skyboxShader;
CGL::Shader brickShader;
CGL::Shader screenShader;
CGL::Shader floorShader;

CGL::Scene scene;

CGL::Cube* lightCube;

unsigned int cubeMapId;
unsigned int cubemapVBO;
unsigned int cubemapVAO;

std::vector<CGL::Light> lights {
    {
        glm::vec3(0.0f, 0.0f, 20.0f),
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


float m_skySize = 1.0f;

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

    CGL::NormalMap normalMap(&window, &camera);
    CGL::FrameBuffer frameBuffer;

    float lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    auto drawCubes = [&scene](CGL::Shader& shader){
        shader.use();

        for (int i = 0; i < scene.meshes().size(); i++) {
            auto m = scene.meshes()[i];
            m->draw(shader);
        }
    };

    CGL::ShadowMap shadowMap;
    CGL::Blend blend;
    CGL::CullFace cullFace;

    while (!glfwWindowShouldClose(window.getWindow())) {
        float currentFrame = glfwGetTime();

        float deltaTime = currentFrame - lastFrame;
        camera.correctSpeed(deltaTime);
        lastFrame = currentFrame;

        inputController.process();

        frameBuffer.bind();

        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double timeVal = glfwGetTime() * 60;

        // screenShader.use();
        // customFramebuffer.bind();

        cubeShader.use();

        CGL::Transform view = camera.getLookAt();
        cubeShader.setMat4("view", view);

        CGL::Transform projection;
        projection.perspective(45.0f, window.aspect(), 1.0f, 100.0f);
        cubeShader.setMat4("projection", projection);

		CGL::Transform model;

		// model.rotate(90.0f, 1.0f, 1.0f, 0.0f);
        cubeShader.setMat4("model", model);
        // model.translate(0.0f, 0.0f, 5.0f);

        cubeShader.setVec3("viewPos", camera.pos());
        cubeShader.setVec3("viewDir", camera.front());

        // cubeShader.setVec3("light.position", glm::vec3(0.0f, 0.0f, 5.0f));
        // cubeShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);

        cubeShader.setVec3("lights[0].position", lights[0].pos);
        cubeShader.setVec3("lights[0].color", lights[0].color);

        // cubeShader.setVec3("lights[1].position", lights[1].pos);
        // cubeShader.setVec3("lights[1].color", lights[1].color);

        // cubeShader.setVec3("lights[2].position", lights[2].pos);
        // cubeShader.setVec3("lights[2].color", lights[2].color);

        cubeShader.setInt("material.diffuse", 0);
        cubeShader.setInt("material.specular", 1);
        // cubeShader.setVec3("material.ambient", 0.1f, 0.1f, 0.1f);
        // cubeShader.setVec3("material.diffuse", 0.0f, 0.0f, 0.5f);
        // cubeShader.setVec3("material.specular", 1.0f, 0.0f, 0.0f);
        cubeShader.setFloat("material.shininess", 252.0f);


        // for (int i = scene.meshes().size()/2 - 1; i < scene.meshes().size(); i++) {
        //     // CGL::Transform rotMod = model;
        //     // rotMod.rotate(count++ * 45.0f + timeVal, 1.0f, 0.0f, 0.0f);
        //     // rotMod.translate(0.0f, 10.0f, 0.0f);

        //     // cubeShader.setMat4("model", rotMod);
        //     cubeShader.use();
        //     auto m = scene.meshes()[i];
        //     m->draw(cubeShader);
        // }

        // --- Light shader ---

        // lightShader.use();
        // model.reset();

        // CGL::Transform mvp = projection * view * model;
        // lightShader.setMat4("MVP", mvp);
        // lightCube->draw(lightShader);

        // --- Normal map ----

        // glClearColor(1.0, 1.0, 1.0, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        frameBuffer.setStencil(GL_ALWAYS, 0xff);

        // drawCubes(cubeShader);

        frameBuffer.setStencil(GL_NOTEQUAL, 0x00);
        frameBuffer.enableDepth(false);

        model.reset();
        // model.translate(2.0, 0.0, -3.0);
        model.scale(1.1f);

        CGL::Transform mvp = projection * view * model;
        stencilShader.use();
        stencilShader.setVec3("timeColor", {0.6, 0.1, 0.8});
        stencilShader.setMat4("MVP", mvp);

        // drawCubes(stencilShader);

        frameBuffer.setStencil(GL_ALWAYS);
        frameBuffer.enableDepth(true);

        // --- FLOOR ---



        // --- Screen shader ---

        // shadowMap.use(window, camera);
        // blend.use(window, camera);
        cullFace.use(window, camera);

        frameBuffer.unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        screenShader.setInt("screen", 0);

        frameBuffer.use();

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

        // --- Skybox ---

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

    std::vector<CGL::TextureBase> cubeTexes {
        CGL::TextureBase::create("textures/container/container.png", "diffuse"),
        CGL::TextureBase::create("textures/container/container_border.png", "specular")
    };

    // Skybox [begin]

    cubeMapId = CGL::TextureBase::loadCubmap(
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




    // Skybox [end]

    // CGL::Cube* cube1 = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f), cubeTexes);
    // CGL::Cube* cube2 = new CGL::Cube(glm::vec3(5.0f, 0.0f, 0.0f), cubeTexes);
    // CGL::Cube* cube3 = new CGL::Cube(glm::vec3(0.0f, 0.0f, -5.0f), cubeTexes);
    // CGL::Cube* cube4 = new CGL::Cube(glm::vec3(-5.0f, 0.0f, 0.0f), cubeTexes);

    // for (int i = 0; i < 1; i++) {
    //     i = i + 4;
    //     // CGL::Cube* cube = new CGL::Cube;
    //     CGL::Cube* cube = new CGL::Cube(glm::vec3(i + (-2.0f), i + 0.0f, i*(i+2) + 1.0f), cubeTexes, (i+1));
    //     scene.addMesh(cube);
    // }

    CGL::Cube* cube = new CGL::Cube(glm::vec3(0.0f, 0.0f, 0.0f), cubeTexes, 1);
    scene.addMesh(cube);


    lightCube = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f));


    cubeShader    = CGL::Shader("shaders/cube.vert",    "shaders/cube.frag");
    stencilShader = CGL::Shader("shaders/stencil.vert", "shaders/stencil.frag");
    floorShader   = CGL::Shader("shaders/floor.vert", "shaders/floor.frag");

    lightShader  = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    modelShader  = CGL::Shader("shaders/model.vert", "shaders/model.frag");
    skyboxShader = CGL::Shader("shaders/skybox.vert", "shaders/skybox.frag");
    screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");

	return loop();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
