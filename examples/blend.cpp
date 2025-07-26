#include <examples/blend.h>
#include <glad/glad.h>

#include <cgl/mesh/2D/rectangle.h>
#include <cgl/mesh/3D/cube.h>

#include <cgl/texture/textureloader.h>

CGL::Blend::Blend()
{
    m_shader = CGL::Shader("shaders/blend.vert", "shaders/blend.frag");
    CGL::TextureBase winTex = CGL::TextureLoader::loadFromFile("textures/window/blending_transparent_window.png", true);
    CGL::TextureBase contTex = CGL::TextureLoader::loadFromFile("textures/container/container.png", true);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    for (int i = 0; i < 3; i++) {
        m_scene.addMesh(new CGL::Cube(contTex));
        m_scene.addMesh(new CGL::Rectangle(winTex));
    }

    // m_scene.addMesh(new CGL::Cube({0.0, 0.0, 0.0}, m_grassTex));
}

void CGL::Blend::use(const CGL::Window &window, const CGL::Camera &camera)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CGL::Transform model;
    CGL::Transform view = camera.getLookAt();
    CGL::Transform projection;
    projection.perspective(45.0, window.aspect(), 1.0, 100);

    m_shader.use();
    m_shader.setMVP(model, view, projection);
    m_shader.setInt("grassTexture", 0);

    for (const auto& m: m_scene.meshes()) {
        // model.reset();
        static int count = 0;
        model.scale(count % 2 == 0 ? 2 : 1);
        model.translateX(count % 2 == 0 ? 0 : 0);
        model.translateY(count % 2 == 0 ? 0.5 : 0);
        model.translateZ(count % 2 == 0 ? -2 : 1.1);
        count = count == 2 ? 0 : count;
        ++count;

        m_shader.setMat4("model", model);
        m->draw(m_shader);
    }

    glDisable(GL_BLEND);
}
