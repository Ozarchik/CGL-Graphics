#ifndef CGL_ENGINE_H
#define CGL_ENGINE_H

#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/framebuffer.h>
#include <cgl/core/camera.h>


namespace CGL {
struct View {
    std::unique_ptr<Camera> camera;
    std::unique_ptr<FrameBuffer> framebuffer;
    bool postprocessing = false;
};

class Engine
{
public:
    void setActiveScene(Scene* scene);
    Scene* activeScene() const;

    void setActiveCamera(Camera* camera);
    Camera* activeCamera() const;

    void addView();
    std::vector<View>& views();

    static Engine& instance();
    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine& other) = delete;

    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;

private:
    Engine();

private:
    std::vector<View> m_views;
    Camera* m_camera = nullptr;
    Scene* m_scene = nullptr;
};

Engine& cglEngine();

}

#endif // CGL_ENGINE_H
