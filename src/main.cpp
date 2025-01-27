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
CGL::Scene scene;

CGL::Cube* lightCube;
CGL::Light light(
    glm::vec3(0.0f, 0.0f, 5.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
);

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
    // CGL::Model renderModel("C:/MyCode/CGL-Graphics/assets/backpack/backpack.obj", false);
    // CGL::Model bedModel("C:/MyCode/CGL-Graphics/assets/furniture-pack-3d-model/OBJ/BookCaseLarge.obj", true);
    // CGL::Model samuraiModel("C:/MyCode/CGL-Graphics/assets/-samurai-3d-model/Samurai_Attack-bl.obj", false);
    // CGL::Model chairModel("C:/MyCode/CGL-Graphics/assets/chair/eggchair.obj", true);

    // CGL::Model renderModel("assets/backpack/backpack.obj");
	// CGL::Model renderModel("src/InteriorTest.fbx");

    CGL::InputController inputController(&window, &camera);
    camera.setPos({-2.5f, 2.5f, -5.0f});

    while (!glfwWindowShouldClose(window.getWindow())) {

        inputController.process();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double timeVal = glfwGetTime() * 60;

        cubeShader.use();

		CGL::Transform view = camera.getLookAt();
        cubeShader.setMat4("view", view.data());

		CGL::Transform projection;
        projection.perspective(45.0f, window.width()/window.height(), 1.0f, 100.0f);
        cubeShader.setMat4("projection", projection.data());

		CGL::Transform model;

		// model.rotate(90.0f, 1.0f, 1.0f, 0.0f);
        cubeShader.setMat4("model", model.data());
        model.translate(0.0f, 0.0f, 5.0f);

        cubeShader.setVec3("viewPos", camera.pos());

        cubeShader.setVec3("light.position", glm::vec3(0.0f, 0.0f, 5.0f));
        cubeShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);

        cubeShader.setInt("material.diffuse", 0);
        cubeShader.setInt("material.specular", 1);
        // cubeShader.setVec3("material.ambient", 0.1f, 0.1f, 0.1f);
        // cubeShader.setVec3("material.diffuse", 0.0f, 0.0f, 0.5f);
        // cubeShader.setVec3("material.specular", 1.0f, 0.0f, 0.0f);
        cubeShader.setFloat("material.shininess", 252.0f);

        cubeShader.setVec3("viewDir", camera.pos());

        int count = 1;
        for (const auto& m: scene.meshes()) {
            CGL::Transform rotMod = model;
            // rotMod.rotate(count++ * 90.0f, 0.0f, 0.0f, 1.0f);
            // rotMod.translate(5.0f, 0.0f, 0.0f);

            cubeShader.setMat4("model", rotMod.data());
            cubeShader.use();
            m->draw(cubeShader);
        }

        // --- Light shader ---

        lightShader.use();
        model.reset();
        CGL::Transform mvp = projection * view * model;
        lightShader.setMat4("MVP", mvp.data());
        lightCube->draw(lightShader);

        // --- Model shader ---

        // modelShader.use();

        // modelShader.setMat4("model", model.data());
        // modelShader.setMat4("view", view.data());
        // modelShader.setMat4("projection", projection.data());

        // renderModel.draw(modelShader);

        // model.reset();
        // model.translate(5.0f, 0.0f, 0.0f);

        // modelShader.setMat4("model", model.data());
        // bedModel.draw(modelShader);

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

    CGL::Cube* cube1 = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f), cubeTexes);
    CGL::Cube* cube2 = new CGL::Cube(glm::vec3(5.0f, 0.0f, 0.0f), cubeTexes);
    CGL::Cube* cube3 = new CGL::Cube(glm::vec3(0.0f, 0.0f, -5.0f), cubeTexes);
    CGL::Cube* cube4 = new CGL::Cube(glm::vec3(-5.0f, 0.0f, 0.0f), cubeTexes);
    CGL::Sphere* sphere = new CGL::Sphere();
    lightCube = new CGL::Cube(glm::vec3(0.0f, 0.0f, 5.0f));

    scene.addMesh(cube1);
    scene.addMesh(cube2);
    scene.addMesh(cube3);
    scene.addMesh(cube4);
    scene.addMesh(sphere);

    cubeShader  = CGL::Shader("shaders/cube.vert",  "shaders/cube.frag");
    lightShader = CGL::Shader("shaders/light.vert", "shaders/light.frag");
    modelShader = CGL::Shader("shaders/model.vert", "shaders/model.frag");

	return loop();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
