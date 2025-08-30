#ifndef CGL_ANIMATIONTRACK_H
#define CGL_ANIMATIONTRACK_H

#include <vector>
#include <glm/glm.hpp>

namespace cgl {

struct KeyFrame {
    float time;                  // время в секундах
    glm::vec3 position;          // смещение
    glm::vec3 rotation;          // углы Эйлера в радианах
    glm::vec3 scale;             // масштаб

    KeyFrame(float t = 0.0f,
             const glm::vec3& pos = {0,0,0},
             const glm::vec3& rot = {0,0,0},
             const glm::vec3& scl = {1,1,1})
        : time(t), position(pos), rotation(rot), scale(scl) {}

    static KeyFrame makeScale(float time, glm::vec3 scale);
    static KeyFrame makeRotation(float time, glm::vec3 rotation);
    static KeyFrame makeTranslation(float time, glm::vec3 translation);
};

class AnimationTrack {
public:
    void addKeyFrame(const KeyFrame& key) { m_keys.push_back(key); }

    KeyFrame sample(float t) const;

    float duration() const {
        return m_keys.empty() ? 0.0f : m_keys.back().time;
    }

private:
    std::vector<KeyFrame> m_keys;
};

}

#endif // CGL_ANIMATIONTRACK_H
