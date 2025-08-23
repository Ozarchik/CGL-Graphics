#include <cgl/graphics/renderer.h>
#include <cgl/utility/logger.h>
#include <cgl/managers/resourcemanager.h>
#include <glm/glm.hpp>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/graphics/mesh/common/meshbuilder.h>
#include <cgl/core/buffer/vaobufferbuilder.h>

CGL::Renderer::Renderer()
{
}

void CGL::Renderer::render(Scene &scene, View &view)
{
    view.camera->update();
    view.framebuffer->bind();

    CGL::Transform model;
    grid.draw(*view.camera, model.translateY(-15.0f));
    grid.draw(*view.camera, model.translateY(30.0f));
    scene.render(*view.camera);

    view.framebuffer->unbind();
}
