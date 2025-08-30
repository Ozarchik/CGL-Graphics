#ifndef CGL_OBJECT_H
#define CGL_OBJECT_H

#include <cgl/core/event/event.h>

namespace cgl {
class Object
{
    friend class InputController;

public:
    Object();

protected:
    virtual void keyEventHandler(const cgl::KeyEvent& event) {}
    virtual void mouseEventHandler(const cgl::MouseEvent& event) {}
    virtual void mouseWheelEventHandler(const cgl::MouseWheelEvent& event) {}
};
}

#endif // CGL_OBJECT_H
