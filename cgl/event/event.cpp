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

CGL::MouseAction CGL::MouseEvent::type() const
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

CGL::MouseWheelDirection CGL::MouseWheelEvent::direction() const
{
    return m_state.direction;
}

CGL::MouseWheelEvent::MouseWheelEvent(double dx, double dy, const MouseWheelState &state)
    : m_dx(dx), m_dy(dy), m_state(state)
{

}

double CGL::MouseWheelEvent::dx() const
{
    return m_dx;
}

double CGL::MouseWheelEvent::dy() const
{
    return m_dy;
}
