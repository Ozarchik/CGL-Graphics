#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cmath>

// examples
#include <examples/blend.h>
#include <examples/cullface.h>
#include <examples/floor.h>
#include <examples/geometryexample.h>
#include <examples/geometrynormalexample.h>
#include <examples/instancing.h>
#include <examples/planet.h>
#include <examples/lightscene.h>
#include <examples/quadrotonnel.h>
#include <examples/solarsystem.h>
#include <examples/shadowmap.h>

#include <cgl/window.h>

#include <cgl/camera.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/mesh/3D/sphere.h>
#include <cgl/texture/texture.h>
#include <cgl/transform.h>
#include <cgl/model/model.h>
#include <cgl/scene.h>
#include <cgl/shader.h>
#include <cgl/window.h>
#include <cgl/inputcontroller.h>
#include <cgl/normalmap.h>
#include <cgl/framebuffer.h>
#include <cgl/vertexbuffer.h>

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

    glfwSetFramebufferSizeCallback(window.handler(), framebufferSizeCallback);

    glViewport(0, 0, window.width(), window.height());
}

int loop() {					
    CGL::InputController inputController(&window, &camera);

    CGL::NormalMap normalMap(&window, &camera);
    CGL::FrameBuffer frameBuffer;

    float lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_FRAMEBUFFER_SRGB);

    // CGL::ShadowMap shadowMap;
    // CGL::Blend blend;
    // CGL::CullFace cullFace;
    // CGL::Floor floor;
    // CGL::GeometryExample geometryExample;
    // CGL::GeometryNormalExample geomNormalExample;
    // CGL::Instancing instancing;
    // CGL::LightScene lightScene;
    // CGL::Planet planet;
    // CGL::QuadroTonel tonel;
    CGL::SolarSystem solarSystem;

    while (!glfwWindowShouldClose(window.handler())) {
        float currentFrame = glfwGetTime();

        float deltaTime = currentFrame - lastFrame;
        camera.correctSpeed(deltaTime);
        lastFrame = currentFrame;

        inputController.process();

        frameBuffer.bind();

        double timeVal = glfwGetTime() * 60;

        CGL::Transform model, view, projection;
        view = camera.getLookAt();
        projection.perspective(45.0f, window.aspect(), 0.1f, 500.0f);

        // --- EXAMPLES ---

        // shadowMap.use(window, camera);
        // blend.use(window, camera);
        // cullFace.use(window, camera);
        // floor.use(window, camera);
        // geometryExample.use(window, camera);
        // geomNormalExample.use(model, view, projection);
        // instancing.use(model, view, projection);
        // planet.use(model, view, projection);
        // tonel.use(model, view, projection);
        // lightScene.use(camera, model, view, projection);
        solarSystem.use(model, view, projection);

        // static bool pressed = false;
        // if (inputController.isKeySpacePressed()) {
        //     if (!pressed) {
        //         pressed = true;
        //         int static c = 0;
        //         std::cout << "key space pressed: " << c++ << std::endl;
        //         lightScene.gammaOnOff();
        //     }
        // } else {
        //     pressed = false;
        // }

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
