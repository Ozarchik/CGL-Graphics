#include <cgl/application.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>
#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/graphics/scene/node.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/graphics/model/modelloader.h>
#include <cgl/graphics/material/materialbuilder.h>
#include <cgl/core/engine.h>
#include <cgl/core/buffer/vaobufferbuilder.h>


cgl::Application::Application(/*int argc, char *argv[]*/)
    : m_commandDispatcher(m_scene)
    , m_mainwindow(m_commandDispatcher, m_renderer)
{
    cglEngine().setActiveScene(&m_scene);
    // cglEngine().addView();

    createTestObjects();
}

cgl::Application::~Application()
{

}

void cgl::Application::createTestObjects()
{
    cgl::Transform model;

    auto meshShader = cgl::ResourceManager::loadDefaultModelShader();
    model.translateX(10.0f);
    std::shared_ptr<cgl::Node> node = std::make_shared<cgl::Node>(meshShader, model);
    node->addMesh(
        MeshBuilder::build(MeshType::Cube)
            .done(),
        MaterialBuilder::build()
            .addTexture("terrazzo/terrazzo_17_normal-1K.png")
            .enabled(true)
            .done()
    );
    m_scene.append(node);

    std::shared_ptr<cgl::Node> node2 = std::make_shared<cgl::Node>(meshShader, model.translateX(-3.0));
    node2->addMesh(
        MeshBuilder::build(MeshType::Sphere)
            .done(),
        MaterialBuilder::build()
            .addTexture("planets/earth.bmp")
            .enabled(true)
            .done()
    );
    m_scene.append(node2);

    std::shared_ptr<cgl::Node> node3 = std::make_shared<cgl::Node>(meshShader, model.translateX(3.0));
    node3->addMesh(
        MeshBuilder::build(MeshType::Rectangle)
            .done(),
        MaterialBuilder::build()
            .addTexture("brick/brick.jpg")
            .enabled(true)
            .done()
    );
    m_scene.append(node3);
    
    cgl::Transform scaleTransform;
    scaleTransform.scale(0.5);
}

cgl::Application &cgl::Application::instance()
{
    static Application app;
    return app;
}

void cgl::Application::createTerrainExample()
{
    std::shared_ptr heightMapShader = cgl::ResourceManager::loadShader("cpuheight");
    cgl::TextureLoader loader;
    cgl::TextureData textureData = loader.getTextureData(ResourceManager::getTexturePath() + "/heightmap/iceland_heightmap.png");
    auto data = textureData.data;
    int width = textureData.width;
    int height = textureData.height;
    int nChannels = textureData.components;

    int rez = 1;

    std::vector<glm::vec3> vertices;
    float yScale = 64.0f/256.0f;
    float yShift = 50.0f;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char y = data[(j + width*i) * nChannels];

            vertices.push_back({
                -height/2.0f + height*i/(float)height,
                (int) y * yScale - yShift,
                -width/2.0f + width*j/(float)width
            });
        }
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < height-1; i++) {
        for (unsigned int j = 0; j < width; j++) {
            for (unsigned int k = 0; k < 2; k++) {
                indices.push_back(j + width * (i + k*rez));
            }
        }
    }


    auto node = std::make_shared<cgl::Node>(heightMapShader);
    cgl::PrimitiveData primData (
        cgl::Primitive::TriangleStrip,
        cgl::DrawType::Indexes,
        height-1,
        width*2
    );

    std::shared_ptr<Mesh> mesh = MeshBuilder::build(MeshType::Terrain)
            .setVAO(VAOBufferBuilder::build()
                .setVertexData(vertices.data(), vertices.size() * sizeof(glm::vec3), cgl::DrawChangeMode::Static)
                .setIndexData(indices.data(), indices.size() * sizeof(unsigned int), cgl::DrawChangeMode::Static)
                .setAttribute(0, 3, sizeof(glm::vec3), 0)
                .done()
            )
            .setPrimitiveData(primData)
            .done();

    node->addMesh(mesh);

    m_scene.append(node);
}

void cgl::Application::run()
{
    createTerrainExample();
    while (cglCoreContext().isAlive()) {
        cglCoreContext().calcDeltaTime();
        draw();
    }
}

void cgl::Application::draw()
{
    cglErrorsCheck();
    cglCoreContext().update();

    m_commandDispatcher.process();
    cglInputController().process();

    auto& scene = *cglEngine().activeScene();
    auto& views = cglEngine().views();

    // for (auto& view: views) {
    // m_physics.update();
    // m_animation.update();
    views.front().useCustomFramebuffer(false);
    m_renderer.render(scene, views.front());
    // views.front().postprocess();

    cglErrorsCheck();

    // m_mainwindow.render();

    cglInputController().process();
    cglCoreContext().swapBuffers();
}
