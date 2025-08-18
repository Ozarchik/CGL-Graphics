#ifndef CGL_COMMANDDISPATCHER_H
#define CGL_COMMANDDISPATCHER_H

#include <queue>
#include <memory>
#include <cgl/core/command/icommand.h>

namespace CGL {
class CommandDispatcher
{
public:
    CommandDispatcher(Scene& scene);

    void append(std::shared_ptr<CGL::ICommand> command);
    void process();

private:
    CGL::Scene& m_scene;
    std::queue<std::shared_ptr<CGL::ICommand>> m_queue;
};
}

#endif // COMMANDDISPATCHER_H
