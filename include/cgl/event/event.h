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

enum MouseType {
    Move,
    Press,
    Click
};

enum MouseButton {
    NoButton,
    Left,
    Right,
    Middle
};

struct MouseState {
    MouseType type = Move;
    MouseButton button = NoButton;
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
    MouseEvent(int dx, int dy, const MouseType& state = {});

    MouseType type() const;
    MouseButton button() const;

    int dx() const;
    int dy() const;

private:
    MouseState m_state;
    int m_dx, m_dy;
};
}
#endif // EVENT_H
