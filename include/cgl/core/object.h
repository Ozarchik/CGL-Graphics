#ifndef CGL_OBJECT_H
#define CGL_OBJECT_H

#include <cgl/core/event/event.h>

namespace CGL {
class Object
{
    friend class InputController;

public:
    Object();

protected:
    virtual void keyEventHandler(const CGL::KeyEvent& event) {}
    virtual void mouseEventHandler(const CGL::MouseEvent& event) {}
    virtual void mouseWheelEventHandler(const CGL::MouseWheelEvent& event) {}
};
}

#endif // CGL_OBJECT_H
