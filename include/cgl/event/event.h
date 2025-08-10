#ifndef EVENT_H
#define EVENT_H

namespace CGL {
class Event
{
public:
    Event();
};

enum KeyType {
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_Q,
    Key_S,
    Key_W,
    Key_Z,
    Key_Space,
};

enum MouseAction {
    Move,
    Press,
    Release
};

enum MouseButton {
    NoButton,
    Left,
    Right,
    Middle
};

enum MouseWheelDirection {
    Up,
    Down
};


struct MouseState {
    MouseAction type = Move;
    MouseButton button = NoButton;
};

struct MouseWheelState {
    MouseWheelDirection direction;
};

class KeyEvent: public Event
{
public:
    KeyEvent(KeyType keyType);

    KeyType type() const;

private:
    KeyType m_type;
};

class MouseEvent: public Event
{
public:
    MouseEvent(int dx, int y, const MouseState& state = {});

    MouseAction type() const;
    MouseButton button() const;

    int x() const;
    int y() const;

private:
    MouseState m_state;
    int m_x, m_y;
};

class MouseWheelEvent: public Event
{
public:
    MouseWheelEvent(double dx, double dy, const MouseWheelState& state = {});

    double dx() const;
    double dy() const;
    MouseWheelDirection direction() const;

private:
    MouseWheelState m_state;
    double m_dx, m_dy;
};

}
#endif // EVENT_H
