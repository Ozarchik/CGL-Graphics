#ifndef CGL_MATERIALBUILDER_H
#define CGL_MATERIALBUILDER_H

#include <cgl/graphics/material/material.h>

namespace cgl {
class MaterialBuilder
{
public:
    static MaterialBuilder build();

    cgl::MaterialBuilder& addTexture(const std::string& texture);
    cgl::MaterialBuilder& enabled(bool enabled);

    cgl::Material done();

private:
    MaterialBuilder();

private:
    cgl::Material m_material;
};
}

#endif // CGL_MATERIALBUILDER_H
