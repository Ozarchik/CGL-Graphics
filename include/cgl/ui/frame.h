#ifndef CGL_FRAME_H
#define CGL_FRAME_H



namespace CGL {
class Context;

class Frame {
public:
    Frame(CGL::Context* window);
    void update();

private:
    CGL::Context* m_window;
};
}

#endif
