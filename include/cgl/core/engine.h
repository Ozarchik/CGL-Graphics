#ifndef CGL_ENGINE_H
#define CGL_ENGINE_H

#include <cgl/graphics/scene/scene.h>

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

private:
    Engine();

private:
    std::vector<View> m_views;
    Camera* m_camera = nullptr;
    Scene* m_scene = nullptr;
};
}

#endif // CGL_ENGINE_H
