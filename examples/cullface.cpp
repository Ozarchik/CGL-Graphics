#include <examples/cullface.h>
#include <cgl/mesh/3D/cube.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>

unsigned int VBO, VAO;
unsigned int tex;
CGL::CullFace::CullFace()
{
    m_shader = CGL::Shader("shaders/cullface.vert", "shaders/cullface.frag");
    tex = CGL::TextureLoader::loadFromFile("textures/brick/brick.jpg").id;
    // m_scene.append(new CGL::Cube(tex));


    // cullface vertices

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cullFaceVertices), &cullFaceVertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
}

void CGL::CullFace::use(const CGL::Window& window, const CGL::Camera& camera)
{
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    CGL::Transform model, view, projection;
    view = camera.getLookAt();
    projection.perspective(45.0, window.aspect(), 1.0, 100);

    m_shader.use();
    m_shader.setMVP(model, view, projection);

    for (const auto& node: m_scene.nodes()) {
        node->update(m_shader);
    }

    // cullface
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, tex);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
