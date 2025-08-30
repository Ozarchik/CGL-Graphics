#include <cgl/core/command/commanddispatcher.h>

cgl::CommandDispatcher::CommandDispatcher(cgl::Scene& scene)
    : m_scene(scene)
{}

void cgl::CommandDispatcher::append(std::shared_ptr<ICommand> command)
{
    m_queue.push(std::move(command));
}

void cgl::CommandDispatcher::process()
{
    while (!m_queue.empty()) {
        m_queue.front()->execute(m_scene);
        m_queue.pop();
    }
}
