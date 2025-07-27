#ifndef CGL_FRAME_H
#define CGL_FRAME_H

namespace CGL {
class Window;

class Frame {
public:
    Frame(CGL::Window* window);
    void update();

private:
    CGL::Window* m_window;
};
}

#endif