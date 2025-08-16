#ifndef CGL_UIMANAGER_H
#define CGL_UIMANAGER_H

namespace CGL {
class UiManager
{
public:
    static UiManager& instance();
    void init();
    void deinit();
    void newFrame();
    void render();
    void enableDocking();

private:
    UiManager();
};
}

#endif // CGL_UIMANAGER_H
