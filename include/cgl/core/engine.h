#ifndef CGL_ENGINE_H
#define CGL_ENGINE_H

#include <cgl/graphics/scene/scene.h>

namespace CGL {
class Engine
{
public:
    void setActiveScene(Scene* scene);
    Scene* activeScene() const;

    void setActiveCamera(Camera* camera);
    Camera* activeCamera() const;

    static Engine& instance();

private:
    Engine();

private:
    Camera* m_camera = nullptr;
    Scene* m_scene = nullptr;
};
}

#endif // CGL_ENGINE_H
