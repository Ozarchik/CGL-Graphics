#ifndef CGL_ANIMATIONSYSTEM_H
#define CGL_ANIMATIONSYSTEM_H

#include <cgl/graphics/animationtrack.h>

namespace cgl {

class AnimationSystem {
public:
    AnimationSystem();

    void update();

private:
    AnimationTrack m_track;
    AnimationTrack m_track2;
    float m_time = 0.0f;
};

}

#endif // CGL_ANIMATIONSYSTEM_H
