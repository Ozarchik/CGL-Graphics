#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cmath>

// examples
#include "blend.h"
#include "cullface.h"
#include "floor.h"
#include "geometryexample.h"
#include "geometrynormalexample.h"
#include "instancing.h"
#include "planet.h"

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
CGL::Shader screenShader;
CGL::Scene scene;


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
    CGL::InputController inputController(&window, &camera);

    CGL::NormalMap normalMap(&window, &camera);
    CGL::FrameBuffer frameBuffer;

    float lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);

    CGL::ShadowMap shadowMap;
    CGL::Blend blend;
    CGL::CullFace cullFace;
    CGL::Floor floor;
    CGL::GeometryExample geometryExample;
    CGL::GeometryNormalExample geomNormalExample;
    CGL::Instancing instancing;
    CGL::Planet planet;

    while (!glfwWindowShouldClose(window.getWindow())) {
        float currentFrame = glfwGetTime();

        float deltaTime = currentFrame - lastFrame;
        camera.correctSpeed(deltaTime);
        lastFrame = currentFrame;

        inputController.process();

        frameBuffer.bind();

        double timeVal = glfwGetTime() * 60;


        // --- EXAMPLES ---

        // shadowMap.use(window, camera);
        // blend.use(window, camera);
        // cullFace.use(window, camera);
        // floor.use(window, camera);
        // geometryExample.use(window, camera);
        // geomNormalExample.use(model, view, projection);
        // instancing.use(model, view, projection);

        CGL::Transform model, view, projection;
        view = camera.getLookAt();
        projection.perspective(45.0f, window.aspect(), 0.1f, 100.0f);
        planet.use(model, view, projection);

        frameBuffer.unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader.use();
        screenShader.setInt("screen", 0);

        frameBuffer.use();

        window.update();
	}

	return 0;
}

int main()
{
    window.init();
	initOpenGL();

    screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");

	return loop();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
