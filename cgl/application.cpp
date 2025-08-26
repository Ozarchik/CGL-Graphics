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

CGL::Application::Application(/*int argc, char *argv[]*/)
    : m_commandDispatcher(m_scene)
    , m_mainwindow(m_commandDispatcher, m_renderer)
    , m_raycast(m_scene)
{
    cglEngine().setActiveScene(&m_scene);
    // cglEngine().addView();

    // createTestObjects();

    createTestObjects();
}

CGL::Application::~Application()
{

}

void CGL::Application::createTestObjects()
{
    CGL::Transform model;

    model.translateX(10.0f);
    std::shared_ptr<CGL::Node> node = std::make_shared<CGL::Node>(m_meshShader, model);
    node->addMesh(
        MeshBuilder::build(MeshBuilder::MeshType::Cube)
            .done(),
        MaterialBuilder::build()
            .addTexture("terrazzo/terrazzo_17_normal-1K.png")
            .enabled(true)
            .done()
    );
    m_scene.append(node);

    std::shared_ptr<CGL::Node> node2 = std::make_shared<CGL::Node>(m_meshShader, model.translateX(-3.0));
    node2->addMesh(
        MeshBuilder::build(MeshBuilder::MeshType::Sphere)
            .done(),
        MaterialBuilder::build()
            .addTexture("planets/earth.bmp")
            .enabled(true)
            .done()
    );
    m_scene.append(node2);
    
    std::shared_ptr<CGL::Node> node3 = std::make_shared<CGL::Node>(m_meshShader, model.translateX(3.0));
    node3->addMesh(
        MeshBuilder::build(MeshBuilder::MeshType::Rectangle)
            .done(),
        MaterialBuilder
            ::build()
            .addTexture("brick/brick.jpg")
            .enabled(true)
            .done()
    );
    m_scene.append(node3);
    
    CGL::Transform scaleTransform;
    scaleTransform.scale(0.5);
}

CGL::Application &CGL::Application::instance()
{
    static Application app;
    return app;
}

void CGL::Application::createTerrainExample()
{
    std::shared_ptr heightMapShader = CGL::ResourceManager::loadShader("cpuheight");
    CGL::TextureLoader loader;
    std::tuple<std::vector<unsigned char>, glm::vec3> sourceData = loader.getSourceData("D:/MyPrivateProjects/CGL-Graphics/textures/heightmap/iceland_heightmap.png");
    auto data = std::get<0>(sourceData);
    auto size = std::get<1>(sourceData);
    int width = size.x;
    int height = size.y;
    int nChannels = size.z;

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


    auto node = std::make_shared<CGL::Node>(heightMapShader);
    CGL::PrimitiveData primData (
        CGL::RenderContext::Primitive::TriangleStrip,
        CGL::RenderContext::DrawType::Indexes,
        height-1,
        width*2
    );

    std::shared_ptr<Mesh> mesh = MeshBuilder::build(CGL::MeshBuilder::MeshType::Terrain)
            .setVAO(VAOBufferBuilder::build()
                .setVertexData(vertices.data(), vertices.size() * sizeof(glm::vec3), RenderContext::DrawChangeMode::Static)
                .setIndexData(indices.data(), indices.size() * sizeof(unsigned int), RenderContext::DrawChangeMode::Static)
                .setAttribute(0, 3, sizeof(glm::vec3), 0)
                .done()
            )
            .setPrimitiveData(primData)
            .done();

    node->addMesh(mesh);

    m_scene.append(node);
}

void CGL::Application::run()
{
    m_inputController.addSubscriber(&m_raycast);

    createTerrainExample();
    while (cglCoreContext().isAlive()) {
        cglCoreContext().calcDeltaTime();
        draw();
    }
}

void CGL::Application::draw()
{
    cglErrors();
    cglCoreContext().update();

    m_commandDispatcher.process();
    m_inputController.process();

    auto& scene = *cglEngine().activeScene();
    auto& views = cglEngine().views();

    glIsEnabled(GL_CULL_FACE);

    for (auto& view: views) {
        // view.useCustomFramebuffer(false);
        m_renderer.render(scene, view);
    }

    cglErrors();

    m_mainwindow.render();

    m_inputController.process();
    cglCoreContext().swapBuffers();
}
