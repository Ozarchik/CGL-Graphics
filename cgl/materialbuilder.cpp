#include <cgl/materialbuilder.h>
#include <cgl/resourcemanager.h>

CGL::MaterialBuilder::MaterialBuilder()
{}

CGL::MaterialBuilder CGL::MaterialBuilder::build()
{
    return {};
}

CGL::MaterialBuilder &CGL::MaterialBuilder::addTexture(const std::string &texture)
{
    m_material.add(CGL::ResourceManager::loadTexture(texture)); // TODO: need check before add: texture mby non-valid
    return *this;
}

CGL::MaterialBuilder &CGL::MaterialBuilder::enabled(bool enabled)
{
    m_material.setEnabled(enabled);
    return *this;
}

CGL::Material CGL::MaterialBuilder::done()
{
    return m_material;
}
