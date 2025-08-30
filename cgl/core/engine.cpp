#include <cgl/core/engine.h>

cgl::Engine &cgl::Engine::instance()
{
    static Engine engine;
    return engine;
}

void cgl::Engine::setActiveScene(Scene *scene)
{
    assert(scene);
    m_scene = scene;
}

cgl::Scene *cgl::Engine::activeScene() const
{
    return m_scene;
}

cgl::View& cgl::Engine::addView() {
    m_views.emplace_back(
        std::make_unique<Camera>(),
        std::make_unique<FrameBuffer>(),
        std::make_unique<DefaultPostProcessor>()
    );

    return m_views.back();
}

std::vector<cgl::View> &cgl::Engine::views()
{
    return m_views;
}

void cgl::Engine::setActiveCamera(Camera *camera)
{
    assert(camera);
    m_camera = camera;
}

cgl::Camera *cgl::Engine::activeCamera() const
{
    return m_camera;
}

cgl::Engine::Engine()
{
    addView();
    setActiveCamera(m_views.front().camera.get());
}

cgl::Engine &cgl::cglEngine()
{
    return Engine::instance();
}
