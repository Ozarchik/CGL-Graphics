#include <cgl/core/command/commanddispatcher.h>

CGL::CommandDispatcher::CommandDispatcher(CGL::Scene& scene)
    : m_scene(scene)
{}

void CGL::CommandDispatcher::append(std::unique_ptr<ICommand> command)
{
    m_queue.push(std::move(command));
}

void CGL::CommandDispatcher::process()
{
    while (!m_queue.empty()) {
        m_queue.front()->execute(m_scene);
        m_queue.pop();
    }
}
