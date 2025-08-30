#include <cgl/application.h>
#include <cgl/core/engine.h>

int main(int argc, char* argv[])
{
    cgl::Backtrace::init();
    cgl::ResourceManager::init();

    cgl::CoreContext::instance();
    cgl::Engine::instance();
    cgl::Application::instance().run();

    return 0;
}
