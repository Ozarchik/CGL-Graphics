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
    Key_S,
    Key_W,
    Key_Z,
    Key_Space,
};

enum MouseType {
    Key_Left,
    Key_Right,
    Key_Middle
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
    MouseEvent(int dx, int dy);
    MouseEvent(const MouseType& mouseType);
    MouseEvent(const MouseType& mouseType, int dx, int dy);

    MouseType type() const;
    int dx() const;
    int dy() const;

private:
    MouseType m_type;
    int m_dx, m_dy;
};
}
#endif // EVENT_H
