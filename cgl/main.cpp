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
#include <cgl/floorgenerator.h>
#include <cgl/ui/frame.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

CGL::Window window;
CGL::Camera camera;
CGL::Shader screenShader;
CGL::Scene scene;


#ifdef USE_CONAN
#include <cpptrace/cpptrace.hpp>
void faultHandler(int signal)
{
    cpptrace::stacktrace trace = cpptrace::generate_trace();
    trace.print();
    exit(1);
}
#endif

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

    CGL::FloorGenerator floorGen;
    CGL::Frame testFrame(&window);

    while (!glfwWindowShouldClose(window.handler())) {
        inputController.process();
        float currentFrame = glfwGetTime();

        float deltaTime = currentFrame - lastFrame;
        camera.correctSpeed(deltaTime);
        lastFrame = currentFrame;


        frameBuffer.bind();

        double timeVal = glfwGetTime() * 60;

        CGL::Transform model;
        CGL::Transform view = camera.getLookAt();
        CGL::Transform projection = CGL::Transform::makePerspective(45.0f, window.aspect(), 0.1f, 500.0f);

        floorGen.draw(camera, model, view, projection);

        frameBuffer.unbind();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        testFrame.update();
        
        window.update();

        screenShader.use();
        screenShader.setInt("screen", 0);
        frameBuffer.use();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        window.swapBuffers();
	}

	return 0;
}

// How to generate floor:
// -- Use floor generator: init(camera) -> need to read position
// -- z coord is constant: 0 (for example)
// -- for first step just render white color (because ambient color is black)
// -- Need to set:
// -- 1. side of floor 

int main()
{
    #ifdef USE_CPPTRACE
    signal(SIGSEGV, faultHandler); // crash by accessing to not allowed memory
    signal(SIGFPE, faultHandler);  // crash by invalid arithmetic operation
    #endif

    window.init();
	initOpenGL();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.handler(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    


    screenShader = CGL::Shader("shaders/screen.vert", "shaders/screen.frag");

    loop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
