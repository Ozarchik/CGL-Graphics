#ifndef CGL_EVENT_H
#define CGL_EVENT_H

#include <vector>
#include <string>

namespace cgl {

// enum declaration

enum KeyType {
    Key_Unknown,
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_Space,
    Key_Enter,
    Key_Escape,
    Key_Backspace,
    Key_Tab,
    Key_Insert,
    Key_Delete,
    Key_Home,
    Key_End,
    Key_PageUp,
    Key_PageDown,
    Key_Left,
    Key_Right,
    Key_Up,
    Key_Down,
    Key_F1,
    Key_F2,
    Key_F3,
    Key_F4,
    Key_F5,
    Key_F6,
    Key_F7,
    Key_F8,
    Key_F9,
    Key_F10,
    Key_F11,
    Key_F12,
    Key_NumPad_0,
    Key_NumPad_1,
    Key_NumPad_2,
    Key_NumPad_3,
    Key_NumPad_4,
    Key_NumPad_5,
    Key_NumPad_6,
    Key_NumPad_7,
    Key_NumPad_8,
    Key_NumPad_9,
    Key_Plus,
    Key_Minus,
    Key_Asterisk,
    Key_Slash,
    Key_Period,
    Key_Comma,
    Key_Colon,
    Key_Semicolon,
    Key_Apostrophe,
    Key_Quote,
    Key_Backtick,
    Key_Backslash,
    Key_BracketLeft,
    Key_BracketRight,
    Key_CapsLock,
    Key_NumLock,
    Key_ScrollLock,
    Key_PrintScreen,
    Key_Pause
};

enum KeyModifier {
    Key_None  = 0,
    Key_Shift = 1 << 0,
    Key_Ctrl  = 1 << 1,
    Key_Alt   = 1 << 2,
    Key_Super = 1 << 3  // Windows key or Command key
};

enum KeyAction {
    Key_Press,
    Key_Release,
    Key_Repeat  // For key holding
};

enum MouseAction {
    Mouse_Move,
    Mouse_Press,
    Mouse_Release,
    Mouse_DoubleClick,
    Mouse_Enter,
    Mouse_Leave
};

enum MouseButton {
    Mouse_NoButton,
    Mouse_Left,
    Mouse_Right,
    Mouse_Middle
};

enum MouseWheelDirection {
    Up,
    Down
};

enum WindowAction {
    Resize,
    Close,
    FocusIn,
    FocusOut,
    Minimize,
    Maximize,
    Restore
};

struct MouseState {
    MouseAction type = Mouse_Move;
    MouseButton button = Mouse_NoButton;
    KeyModifier modifiers = Key_None;
};

struct MouseWheelState {
    MouseWheelDirection direction;
    KeyModifier modifiers = Key_None;
};

// class declaration

class Event
{
public:
    Event();
    virtual ~Event() = default;
};

class KeyEvent: public Event
{
public:
    KeyEvent(KeyType keyType, KeyAction action, KeyModifier modifiers = Key_None);

    KeyType type() const;
    KeyAction action() const;
    KeyModifier modifiers() const;

private:
    KeyType m_type;
    KeyAction m_action;
    KeyModifier m_modifiers;
};

class MouseEvent: public Event
{
public:
    MouseEvent(int x, int y, const MouseState& state = {});
    MouseEvent(int x, int y, int globalX, int globalY, const MouseState& state = {});

    MouseAction type() const;
    MouseButton button() const;
    KeyModifier modifiers() const;

    int x() const;
    int y() const;
    int globalX() const;
    int globalY() const;

private:
    MouseState m_state;
    int m_x, m_y;
    int m_globalX = 0, m_globalY = 0;
};

class MouseWheelEvent: public Event
{
public:
    MouseWheelEvent(double dx, double dy, const MouseWheelState& state = {});

    double dx() const;
    double dy() const;
    MouseWheelDirection direction() const;
    KeyModifier modifiers() const;

private:
    MouseWheelState m_state;
    double m_dx, m_dy;
};

class WindowEvent: public Event
{
public:
    WindowEvent(WindowAction action, int width = 0, int height = 0);

    WindowAction action() const;
    int width() const;
    int height() const;

private:
    WindowAction m_action;
    int m_width, m_height;
};

} // namespace CGL

#endif // CGL_EVENT_H
