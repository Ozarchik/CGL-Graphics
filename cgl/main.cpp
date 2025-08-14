#include <cgl/application.h>


int main(int argc, char* argv[])
{
    // CGL::Application app(argc, argv);
    CGL::Application::instance().run();
    return 0;
}


