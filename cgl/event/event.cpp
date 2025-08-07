#include <cgl/event/event.h>

CGL::Event::Event()
{
}

CGL::KeyEvent::KeyEvent(CGL::KeyType keyType)
    : Event(), m_type(keyType)
{}

CGL::KeyType CGL::KeyEvent::type() const
{
    return m_type;
}

CGL::MouseEvent::MouseEvent(int x, int y, const MouseState &state)
    : Event(), m_x(x), m_y(y), m_state(state)
{}

CGL::MouseType CGL::MouseEvent::type() const
{
    return m_state.type;
}

CGL::MouseButton CGL::MouseEvent::button() const
{
    return m_state.button;
}

int CGL::MouseEvent::x() const
{
    return m_x;
}

int CGL::MouseEvent::y() const
{
    return m_y;
}
