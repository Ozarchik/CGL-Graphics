#include <cgl/core/engine.h>
#include <cgl/utility/logger.h>

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

void CGL::Engine::addView()
{
    m_views.emplace_back(
        std::make_unique<CGL::Camera>(),
        std::make_unique<CGL::FrameBuffer>(),
        false
    );
    CGL_CheckErros();
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
