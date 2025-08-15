#ifndef CGL_MATERIALBUILDER_H
#define CGL_MATERIALBUILDER_H

#include <cgl/graphics/material/material.h>

namespace CGL {
class MaterialBuilder
{
public:
    static MaterialBuilder build();

    CGL::MaterialBuilder& addTexture(const std::string& texture);
    CGL::MaterialBuilder& enabled(bool enabled);

    CGL::Material done();

private:
    MaterialBuilder();

private:
    CGL::Material m_material;
};
}

#endif // CGL_MATERIALBUILDER_H
