#include <cgl/core/engine.h>

CGL::Engine &CGL::Engine::instance()
{
    static Engine engine;
    return engine;
}

void CGL::Engine::setActiveScene(Scene *scene)
{
    assert(scene);
    m_scene = scene;
}

void CGL::Engine::setActiveCamera(Camera *camera)
{
    assert(camera);
    m_camera = camera;
}

CGL::Camera *CGL::Engine::activeCamera() const
{
    return m_camera;
}

CGL::Scene *CGL::Engine::activeScene() const
{
    return m_scene;
}

CGL::Engine::Engine() {}
