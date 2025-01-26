#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cmath>

#include "buffer.h"
#include "camera.h"
#include "cube.h"
#include "light.h"
#include "texture.h"
#include "transform.h"
#include "model.h"
#include "scene.h"
#include "shader.h"
#include "window.h"

// void processInput();
// void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// void mouseCallback(GLFWwindow* window, double x, double y);

CGL::Window window;
CGL::Shader shader;
CGL::Scene scene;
CGL::Camera camera;

CGL::Mesh* cube = nullptr;
CGL::Mesh* lightCube = nullptr;
CGL::Light light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));

void initOpenGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		std::abort();
	}

	glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, window.width(), window.height());
}

int loop() {					
    // CGL::Model renderModel("src/backpack.obj");
	// CGL::Model renderModel("src/InteriorTest.fbx");

    CGL::InputController inputController(&window, &camera);

    while (!glfwWindowShouldClose(window.getWindow())) {

        inputController.process();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double timeVal = glfwGetTime() * 60;

        shader.use();

		CGL::Transform view = camera.getLookAt();
        shader.setMat4("view", view.data());

		CGL::Transform projection;
        projection.perspective(45.0f, window.width()/window.height(), 1.0f, 100.0f);
        shader.setMat4("projection", projection.data());

		CGL::Transform model;

		// model.rotate(90.0f, 1.0f, 1.0f, 0.0f);
        shader.setMat4("model", model.data());
		model.translate(0.0f, 0.0f, 25.0f);

        shader.setVec3("viewPos", camera.pos());

        shader.setVec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
        shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        shader.setFloat("material.shininess", 64.0f);
        shader.setInt("material.diffuse", 0);
        shader.setInt("material.specular", 1);
//		light.setup(shader);

//		lightShader.use();
//		lightShader.setMat4("model", model.data());
//		lightShader.setMat4("view", view.data());
//		lightShader.setMat4("projection", projection.data());

        scene.render(shader);
		// scene.render(lightShader);
		
        // renderModel.draw(shader);

        window.update();
	}

	return 0;
}

int main()
{
    window.init();
	initOpenGL();

    cube = new CGL::Cube(glm::vec3(3.0f, 3.0f, 2.0f));
	lightCube = new CGL::Cube(glm::vec3(1.0f, 1.0f, -4.0f));

	// texture1.loadImage("src/container2.png", CGL::RGBA);
	// texture2.loadImage("src/container2_specular.png", CGL::RGBA);

	scene.addMesh(cube);
	scene.addMesh(lightCube);

    shader = CGL::Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    // lightShader = CGL::Shader("shaders/vertexLight.glsl", "shaders/fragmentLight.glsl");

	return loop();
}

// void processInput()
// {
//     auto window = window.getWindow();

// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window.getWindow(), true);

// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 		camera.stepFront();

// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 		camera.stepBack();

// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 		camera.stepLeft();

// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 		camera.stepRight();

// 	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
// 	    camera.stepDown();

// 	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
// 		camera.stepUp();
// }

// void framebufferSizeCallback(GLFWwindow* window, int width, int height)
// {
// 	glViewport(0, 0, width, height);
// }

// void mouseCallback(GLFWwindow* window, double x, double y)
// {
//     camera.rotate(x, y);
// }
