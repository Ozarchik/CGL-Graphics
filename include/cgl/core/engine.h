#ifndef CGL_ENGINE_H
#define CGL_ENGINE_H

#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/framebuffer.h>
#include <cgl/managers/resourcemanager.h>
#include <cgl/core/rendercontext.h>
#include <cgl/core/camera.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <cgl/graphics/postprocess/defaultpostprocessor.h>

namespace cgl {

struct View {
    std::unique_ptr<Camera> camera;
    std::unique_ptr<FrameBuffer> framebuffer;
    std::unique_ptr<IPostProcessPass> postprocessor;

    void useCustomFramebuffer(bool status) {
        if (!framebuffer)
            return;

        if (status)
            framebuffer->bindCustomFramebuffer();
        else
            framebuffer->bindDefaultFramebuffer();
    }

    void postprocess() {
        if (postprocessor && framebuffer) {
            postprocessor->apply(*framebuffer);
        }
    }
};

class Engine
{
public:

    void setActiveScene(Scene* scene);
    Scene* activeScene() const;

    void setActiveCamera(Camera* camera);
    Camera* activeCamera() const;

    View& addView();
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
