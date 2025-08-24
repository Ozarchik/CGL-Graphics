#include <cgl/application.h>
#include <cgl/graphics/mesh/meshes2D.h>
#include <cgl/graphics/mesh/meshes3D.h>
#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/graphics/scene/node.h>
#include <cgl/ui/mainwindow.h>
#include <cgl/graphics/model/modelloader.h>
#include <cgl/utility/logger.h>
#include <cgl/graphics/material/materialbuilder.h>
#include <cgl/core/engine.h>
#include <cgl/core/buffer/vaobufferbuilder.h>
#include <iostream>

float screenVertices[] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

unsigned int quadVAO, quadVBO;

CGL::Application::Application(/*int argc, char *argv[]*/)
    : m_commandDispatcher(m_scene)
    , m_inputController(cglEngine().activeCamera())
    , m_mainwindow(m_commandDispatcher, m_renderer)
    , m_raycast(m_scene, *cglEngine().activeCamera())
{
    cglEngine().setActiveScene(&m_scene);
    // cglEngine().addView();

    m_meshShader = CGL::ResourceManager::loadDefaultShader();
    // createTestObjects();

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
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

CGL::Shader heightMapShader;
GLuint terrainVAO, terrainVBO, terrainEBO;
// int numStrips;
// int numTrisPerStrip;
// void createTerrain()
// {
//     heightMapShader = CGL::ResourceManager::loadShader("cpuheight");
//     // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//     stbi_set_flip_vertically_on_load(true);
//     int width, height, nrChannels;
//     unsigned char *data = stbi_load("D:/MyPrivateProjects/CGL-Graphics/textures/heightmap/default.jpg", &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }

//     std::vector<float> vertices;
//     float yScale = 64.0f / 256.0f, yShift = 16.0f;
//     int rez = 1;
//     unsigned bytePerPixel = nrChannels;
//     for(int i = 0; i < height; i++)
//     {
//         for(int j = 0; j < width; j++)
//         {
//             unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
//             unsigned char y = pixelOffset[0];

//             // vertex
//             vertices.push_back( -height/2.0f + height*i/(float)height );   // vx
//             vertices.push_back( (int) y * yScale - yShift);   // vy
//             vertices.push_back( -width/2.0f + width*j/(float)width );   // vz
//         }
//     }
//     std::cout << "Loaded " << vertices.size() / 3 << " vertices" << std::endl;
//     stbi_image_free(data);

//     std::vector<unsigned> indices;
//     for(unsigned i = 0; i < height-1; i += rez)
//     {
//         for(unsigned j = 0; j < width; j += rez)
//         {
//             for(unsigned k = 0; k < 2; k++)
//             {
//                 indices.push_back(j + width * (i + k*rez));
//             }
//         }
//     }
//     std::cout << "Loaded " << indices.size() << " indices" << std::endl;

//     numStrips = (height-1)/rez;
//     numTrisPerStrip = (width/rez)*2-2;
//     std::cout << "Created lattice of " << numStrips << " strips with " << numTrisPerStrip << " triangles each" << std::endl;
//     std::cout << "Created " << numStrips * numTrisPerStrip << " triangles total" << std::endl;

//     // first, configure the cube's VAO (and terrainVBO + terrainIBO)
//     glGenVertexArrays(1, &terrainVAO);
//     glBindVertexArray(terrainVAO);

//     glGenBuffers(1, &terrainVBO);
//     glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glGenBuffers(1, &terrainEBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
// }

void CGL::Application::createTerrainExample()
{
    heightMapShader = CGL::ResourceManager::loadShader("cpuheight");
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
    float yShift = 16.0f;

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

    auto node = std::make_shared<CGL::Node>(heightMapShader, CGL::Transform{});
    CGL::PrimitiveData primData;
    primData.type = CGL::RenderContext::Primitive::TriangleStrip;
    primData.drawType = CGL::RenderContext::DrawType::Indexes;
    primData.size = height-1;
    primData.offset = width*2;

    CGL::Mesh* mesh = MeshBuilder::build(CGL::MeshBuilder::MeshType::Terrain)
            .setVAO(
                VAOBufferBuilder::build()
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
    glEnable(GL_DEPTH_TEST);

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
