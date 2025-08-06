#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <glad/glad.h>

#include <cgl/shader.h>
#include <cgl/mesh/common/mesh.h>
#include <cgl/texture/texture.h>

namespace CGL {
class Model
{
public:
    Model() = default;
    // Model(const std::vector<CGL::Mesh>& meshes);

    void draw(Shader& shader);

private:
    // std::vector<CGL::Mesh> m_meshes;
    std::vector<CGL::Texture> m_textures;
};
}

#endif // MODEL_H
