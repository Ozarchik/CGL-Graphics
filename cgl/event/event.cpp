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

CGL::MouseEvent::MouseEvent(int dx, int dy)
    : Event(), m_dx(dx), m_dy(dy)
{}

CGL::MouseEvent::MouseEvent(const MouseType &mouseType)
    : Event(), m_type(mouseType)
{}

CGL::MouseEvent::MouseEvent(const MouseType &mouseType, int dx, int dy)
    : Event(), m_type(mouseType), m_dx(dx), m_dy(dy)
{}

CGL::MouseType CGL::MouseEvent::type() const
{
    return m_type;
}

int CGL::MouseEvent::dx() const
{
    return m_dx;
}

int CGL::MouseEvent::dy() const
{
    return m_dy;
}
