#include <cgl/graphics/material/materialbuilder.h>
#include <cgl/managers/resourcemanager.h>

cgl::MaterialBuilder::MaterialBuilder()
{}

cgl::MaterialBuilder cgl::MaterialBuilder::build()
{
    return {};
}

cgl::MaterialBuilder &cgl::MaterialBuilder::addTexture(const std::string &texture)
{
    m_material.add(cgl::ResourceManager::loadTexture(texture)); // TODO: need check before add: texture mby non-valid
    return *this;
}

cgl::MaterialBuilder &cgl::MaterialBuilder::enabled(bool enabled)
{
    m_material.setEnabled(enabled);
    return *this;
}

cgl::Material cgl::MaterialBuilder::done()
{
    return m_material;
}
