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

CGL::MouseEvent::MouseEvent(int dx, int dy, const MouseType &state)
    : Event(), m_dx(dx), m_dy(dy), m_state(state)
{}

CGL::MouseType CGL::MouseEvent::type() const
{
    return m_state.type;
}

CGL::MouseButton CGL::MouseEvent::button() const
{
    return m_state.button;
}

int CGL::MouseEvent::dx() const
{
    return m_dx;
}

int CGL::MouseEvent::dy() const
{
    return m_dy;
}
