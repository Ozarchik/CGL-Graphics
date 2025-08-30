#ifndef CGL_UIMANAGER_H
#define CGL_UIMANAGER_H

namespace cgl {
class UiManager
{
public:
    static UiManager& instance();
    void init();
    void deinit();
    void newFrame();
    void render();
    void setDocking(bool docking);

private:
    UiManager();
    bool m_docking = false;
};
}

#endif // CGL_UIMANAGER_H
