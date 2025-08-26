#include <cgl/application.h>
#include <cgl/core/engine.h>

int main(int argc, char* argv[])
{
    CGL::Backtrace::init();
    CGL::ResourceManager::init();

    CGL::CoreContext::instance();
    CGL::Engine::instance();
    CGL::Application::instance().run();

    return 0;
}
