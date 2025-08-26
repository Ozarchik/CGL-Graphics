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

CGL::Scene *CGL::Engine::activeScene() const
{
    return m_scene;
}

CGL::View& CGL::Engine::addView() {
    m_views.emplace_back(
        std::make_unique<Camera>(),
        std::make_unique<FrameBuffer>(),
        std::make_unique<DefaultPostProcessor>()
    );

    return m_views.back();
}

std::vector<CGL::View> &CGL::Engine::views()
{
    return m_views;
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

CGL::Engine::Engine()
{
    addView();
    setActiveCamera(m_views.front().camera.get());
}

CGL::Engine &CGL::cglEngine()
{
    return Engine::instance();
}
