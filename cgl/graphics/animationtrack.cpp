#include <cgl/graphics/animationtrack.h>
#include <glm/glm.hpp>
#include <cmath>

CGL::KeyFrame CGL::AnimationTrack::sample(float t) const {
    if (m_keys.empty())
        return KeyFrame();

    if (m_keys.size() == 1)
        return m_keys.front();

    float animTime = fmod(t, duration());

    for (size_t i = 0; i < m_keys.size() - 1; ++i) {
        const KeyFrame& k1 = m_keys[i];
        const KeyFrame& k2 = m_keys[i+1];

        if (animTime >= k1.time && animTime <= k2.time) {
            float alpha = (animTime - k1.time) / (k2.time - k1.time);

            glm::vec3 pos = glm::mix(k1.position, k2.position, alpha);
            glm::vec3 rot = glm::mix(k1.rotation, k2.rotation, alpha);
            glm::vec3 scl = glm::mix(k1.scale, k2.scale, alpha);

            return KeyFrame(animTime, pos, rot, scl);
        }
    }

    return m_keys.back();
}

CGL::KeyFrame CGL::KeyFrame::makeRotation(float time, glm::vec3 rotation)
{
    return KeyFrame(time, glm::vec3(0.0f), rotation, glm::vec3(1.0f));
}

CGL::KeyFrame CGL::KeyFrame::makeScale(float time, glm::vec3 scale)
{
    return KeyFrame(time, glm::vec3(0.0f), glm::vec3(0.0f), scale);
}

CGL::KeyFrame CGL::KeyFrame::makeTranslation(float time, glm::vec3 translation)
{
    return KeyFrame(time, translation, glm::vec3(0.0f), glm::vec3(1.0f));
}
