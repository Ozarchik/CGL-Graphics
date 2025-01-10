#ifndef JUSTMESH_H
#define JUSTMESH_H

#include "mesh.h"
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderprogram.h"

namespace CGL {
class JustMesh : public Mesh {
public:
    JustMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureBase> textures);

    void setup() override;
    void draw(ShaderProgram& shaderProgram) override;
};
};

#endif // JUSTMESH_H
