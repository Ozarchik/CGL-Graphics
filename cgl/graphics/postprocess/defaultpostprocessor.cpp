#include <cgl/graphics/postprocess/defaultpostprocessor.h>
#include <cgl/managers/resourcemanager.h>
#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <array>

static std::array<glm::vec4, 6> quad {
    glm::vec4{-1.0f,  1.0f,  0.0f, 1.0f},
    glm::vec4{-1.0f, -1.0f,  0.0f, 0.0f},
    glm::vec4{1.0f, -1.0f,  1.0f, 0.0f},

    glm::vec4{-1.0f,  1.0f,  0.0f, 1.0f},
    glm::vec4{1.0f, -1.0f,  1.0f, 0.0f},
    glm::vec4{1.0f,  1.0f,  1.0f, 1.0f}
};

cgl::DefaultPostProcessor::DefaultPostProcessor()
{
    m_shader = cgl::ResourceManager::loadShader("postprocessing_default");
    auto&& vao = VAOBufferBuilder::build()
                .setVertexData(quad.data(), quad.size() * sizeof(glm::vec4), RenderContext::Static)
                .setAttribute(0, 2, sizeof(glm::vec4), 0)
                .setAttribute(1, 2, sizeof(glm::vec4), sizeof(glm::vec2))
                .done();

    m_quad = cgl::MeshBuilder::build(MeshType::Mesh)
            .setVAO(std::move(vao))
            .setPrimitiveData(PrimitiveData(RenderContext::Triangle, RenderContext::Elements, 6, 0))
            .done();

    m_targetFrambuffer.bindCustomFramebuffer();
}

void cgl::DefaultPostProcessor::apply(FrameBuffer &fbuffer)
{
    m_targetFrambuffer.bind();

    cglCoreContext().update();
    cglRenderContext().setPolygoneMode(cgl::RenderContext::PolygoneMode::Fill);
    m_shader->use();
    m_shader->setInt("screenTexture", 0);
    Texture::bind2D(fbuffer.texture(), 0);
    m_quad->draw(*m_shader);
    Texture::unbind2D(0);
    m_shader->done();

    m_targetFrambuffer.unbind();
}

