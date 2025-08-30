#include <cgl/core/event/event.h>

cgl::Event::Event()
{
}

cgl::KeyEvent::KeyEvent(KeyType keyType, KeyAction action, KeyModifier modifiers)
    : Event(), m_type(keyType), m_action(action), m_modifiers(modifiers)
{

}

cgl::KeyType cgl::KeyEvent::type() const
{
    return m_type;
}

cgl::MouseEvent::MouseEvent(int x, int y, const MouseState &state)
    : Event(), m_x(x), m_y(y), m_state(state)
{}

cgl::MouseAction cgl::MouseEvent::type() const
{
    return m_state.type;
}

cgl::MouseButton cgl::MouseEvent::button() const
{
    return m_state.button;
}

int cgl::MouseEvent::x() const
{
    return m_x;
}

int cgl::MouseEvent::y() const
{
    return m_y;
}


cgl::MouseWheelEvent::MouseWheelEvent(double dx, double dy, const MouseWheelState &state)
    : m_dx(dx), m_dy(dy), m_state(state)
{

}

double cgl::MouseWheelEvent::dx() const
{
    return m_dx;
}

double cgl::MouseWheelEvent::dy() const
{
    return m_dy;
}

cgl::KeyModifier cgl::MouseWheelEvent::modifiers() const
{
    return m_state.modifiers;
}

cgl::MouseWheelDirection cgl::MouseWheelEvent::direction() const
{
    return m_state.direction;
}

cgl::WindowEvent::WindowEvent(WindowAction action, int width, int height)
    : Event(), m_action(action), m_width(width), m_height(height)
{

}

int cgl::WindowEvent::width() const
{
    return m_width;
}

int cgl::WindowEvent::height() const
{
    return m_height;
}

cgl::WindowAction cgl::WindowEvent::action() const
{
    return m_action;
}
