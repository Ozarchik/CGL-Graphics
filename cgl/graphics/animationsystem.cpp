// #include <cgl/graphics/animationsystem.h>
// #include <cgl/core/engine.h>
// #include <cgl/core/corecontext.h>

// CGL::AnimationSystem::AnimationSystem() {}

// void CGL::AnimationSystem::update()
// {
//     auto scene = cglEngine().activeScene();
//     auto tick = cglCoreContext().deltaTime();

//     for (auto& node: scene->nodes()) {
//         node->transformRef().rotateY(tick);
//     }
// }
#include <cgl/graphics/animationsystem.h>
#include <cgl/graphics/animationtrack.h>
#include <cgl/core/engine.h>
#include <cgl/core/corecontext.h>
#include <cgl/graphics/scene/scene.h>
#include <cgl/graphics/scene/node.h>
#include <cgl/core/transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CGL::AnimationSystem::AnimationSystem() {
    m_track.addKeyFrame(KeyFrame::makeRotation(0.0f,  glm::vec3(0.0f, 0.0f, 0.0f)));
    m_track.addKeyFrame(KeyFrame::makeRotation(3.0f,  glm::vec3(0.0f, -45.0f, 0.0f)));
    m_track.addKeyFrame(KeyFrame::makeRotation(6.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
    m_track.addKeyFrame(KeyFrame::makeRotation(9.0f, glm::vec3(0.0f, 45.0f, 0.0f)));
    m_track.addKeyFrame(KeyFrame::makeRotation(12.0f, glm::vec3(0.0f, 0.0f, 0.0f)));

    m_track2.addKeyFrame(KeyFrame(0.0f,  glm::vec3(-20.0f), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0f)));
    m_track2.addKeyFrame(KeyFrame(2.0f,  glm::vec3(-10.5f), glm::vec3(20, 1.0, 20), glm::vec3(1.5f)));
    m_track2.addKeyFrame(KeyFrame(4.0f,  glm::vec3(0.0f),   glm::vec3(40, 1.0, 40), glm::vec3(3.0f)));
    m_track2.addKeyFrame(KeyFrame(6.0f,  glm::vec3(0.5f),   glm::vec3(60, 1.0, 60), glm::vec3(6.5f)));
    m_track2.addKeyFrame(KeyFrame(8.0f, glm::vec3(10.0f),  glm::vec3(80, 1.0, 80), glm::vec3(12.f)));
    m_track2.addKeyFrame(KeyFrame(10.0f, glm::vec3(20.0f),  glm::vec3(100, 1.0, 100), glm::vec3(24.0f)));

    m_track2.addKeyFrame(KeyFrame(12.0f, glm::vec3(20.0f),  glm::vec3(100, 1.0, 100), glm::vec3(24.0f)));
    m_track2.addKeyFrame(KeyFrame(14.0f, glm::vec3(10.0f),  glm::vec3(80, 1.0, 80), glm::vec3(12.f)));
    m_track2.addKeyFrame(KeyFrame(16.0f,  glm::vec3(0.5f),   glm::vec3(60, 1.0, 60), glm::vec3(6.5f)));
    m_track2.addKeyFrame(KeyFrame(18.0f,  glm::vec3(0.0f),   glm::vec3(40, 1.0, 40), glm::vec3(3.0f)));
    m_track2.addKeyFrame(KeyFrame(20.0f,  glm::vec3(-10.5f), glm::vec3(20, 1.0, 20), glm::vec3(1.5f)));
    m_track2.addKeyFrame(KeyFrame(22.0f,  glm::vec3(-20.0f), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0f)));
}

void CGL::AnimationSystem::update() {
    auto scene = cglEngine().activeScene();
    float dt = cglCoreContext().deltaTime();
    m_time += dt;

    KeyFrame frame = m_track2.sample(m_time);

    auto node1 = scene->nodes().front().get();
    // for (auto& node : scene->nodes().front()) {
    Transform t;
    t.reset()
        .translate(frame.position)
        .rotateX(frame.rotation.x)
        .rotateY(frame.rotation.y)
        .rotateZ(frame.rotation.z)
        .scale(frame.scale.x, frame.scale.y, frame.scale.z);
    // .scale(frame.scale.x, frame.scale.y, frame.scale.z);

    node1->setTransform(t);
    // KeyFrame frame2 = m_track.sample(m_time);

    // auto node2 = scene->nodes().back().get();
    // // for (auto& node : scene->nodes().front()) {
    //     t.reset()
    //         .rotateX(frame2.rotation.x)
    //         .rotateY(frame2.rotation.y)
    //         .rotateZ(frame2.rotation.z);

    //     node2->setTransform(t);
    // }
}
