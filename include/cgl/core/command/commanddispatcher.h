#ifndef CGL_COMMANDDISPATCHER_H
#define CGL_COMMANDDISPATCHER_H

#include <queue>
#include <memory>
#include <cgl/core/command/icommand.h>

namespace cgl {
class CommandDispatcher
{
public:
    CommandDispatcher(Scene& scene);

    void append(std::shared_ptr<cgl::ICommand> command);
    void process();

private:
    cgl::Scene& m_scene;
    std::queue<std::shared_ptr<cgl::ICommand>> m_queue;
};
}

#endif // COMMANDDISPATCHER_H
