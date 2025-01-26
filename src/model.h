#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <string>

#include "shader.h"
#include "texturebase.h"
#include "mesh.h"

namespace CGL {
class Model {
public:
    Model(const std::string& filepath);

    void draw(CGL::Shader& Shader);
    void load(const std::string& filepath);

private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<TextureBase> loadTextures(aiMaterial* material, aiTextureType type, std::string typeName);
    unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);

private:
    std::vector<CGL::Mesh> m_meshes;
    std::string m_directory;
    std::vector<TextureBase> textures_loaded;
};
};
