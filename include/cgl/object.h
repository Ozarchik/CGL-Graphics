#ifndef OBJECT_H
#define OBJECT_H

#include <cgl/event/event.h>

namespace CGL {
class Object
{
public:
    Object();

    virtual void keyEventHandler(const CGL::KeyEvent& event) {}
    virtual void mouseEventHandler(const CGL::MouseEvent& event) {}
};
}

#endif // OBJECT_H
