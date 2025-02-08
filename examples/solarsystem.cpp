#include "solarsystem.h"
#include "sphere.h"
#include "textureloader.h"

constexpr int kDistance = 15.0;
constexpr int kRadius = 2.0;

CGL::SolarSystem::SolarSystem()
{
    m_shader = CGL::Shader("shaders/cube.vert", "shaders/cube.frag");

    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/sun.jpg")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/mercury.jpg")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/venus.jpg")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/earth.bmp")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/moon.bmp")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/mars.jpg")));
    m_scene.addMesh(new CGL::Sphere(CGL::TextureLoader::loadFromFile("textures/planets/jupiter.jpg")));

    m_info.emplace_back(PlanetInfo{kDistance * 0.000f, kRadius * 5.000f, 200.001f, 365.00f, kDistance * 0.0000f, 1.0f});
    m_info.emplace_back(PlanetInfo{kDistance * 0.387f, kRadius * 0.382f, 58.6000f, 87.600f, kDistance * 0.0000f, 1.00f});
    m_info.emplace_back(PlanetInfo{kDistance * 0.720f, kRadius * 0.949f, 243.000f, 224.50f, kDistance * 0.0000f, 1.00f});
    m_info.emplace_back(PlanetInfo{kDistance * 1.000f, kRadius * 1.000f, 1.00000f, 365.00f, kDistance * 0.0000f, 0.3f});
    m_info.emplace_back(PlanetInfo{kDistance * 1.000f, kRadius * 0.273f, 10.1250f, 365.45f, kDistance * 0.1500f, 27.00f});
    m_info.emplace_back(PlanetInfo{kDistance * 1.523f, kRadius * 0.531f, 1.02500f, 686.20f, kDistance * 0.0000f, 1.00f});
    m_info.emplace_back(PlanetInfo{kDistance * 5.220f, kRadius * 5.970f, 0.72000f, 4328.9f, kDistance * 0.0000f, 1.00f});
}

void CGL::SolarSystem::use(
    CGL::Transform& model,
    CGL::Transform& view,
    CGL::Transform& projection
)
{
    m_shader.use();
    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_shader.setBool("useColor", false);

    m_shader.setVec3("light.color", 1.0, 1.0, 1.0);
    m_shader.setVec3("light.position", 0.0, 0.0, 0.0);
    m_shader.setInt("diffuseTex", 0);

    static float count = 0.0f;
    float x, y;

    for (int i = 0; i < m_scene.meshes().size(); i++) {

        model.reset();
        model.translateZ(-35.0f);
        model.rotate(90.0, 1.0, 0.0, 0.0);
        model.translateX(-15.0f);
        x = m_info[i].distance * cosf(count/m_info[i].yearPeriod * 6.28);
        y = m_info[i].distance * sinf(count/m_info[i].yearPeriod * 6.28);
        model.translate(x, 0.0, y);

        float moonX, moonY;
        moonX = m_info[i].moonDistance * cosf(count/m_info[i].moonPeriod * 6.28f);
        moonY = m_info[i].moonDistance * sinf(count/m_info[i].moonPeriod * 6.28f);
        model.translate(moonX, 0.0f, moonY);
        model.rotate(-count/m_info[i].localPeriod * 360, 0.0, 1.0, 0.0);
        model.rotate(-90.0f, 1.0f, 0.0f, 0.0f);
        model.scale(m_info[i].radius);

        m_shader.setMat4("model", model);
        m_scene.meshes()[i]->draw(m_shader);
    }

    count += 0.1f;
}
