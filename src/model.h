#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <texturebase.h>
#include <string>

#include <glad/glad.h>

#include "shader.h"
#include "mesh.h"

namespace CGL {
class Model
{
public:
    Model() = default;
    Model(const std::vector<CGL::Mesh>& meshes);

    void draw(Shader& shader);

private:
    std::vector<CGL::Mesh> m_meshes;
    std::vector<CGL::TextureBase> m_textures;
};
}

#endif // MODEL_H
