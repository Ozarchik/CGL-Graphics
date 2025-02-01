#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <string>

#include "shader.h"
#include "texturebase.h"
#include "mesh.h"

using std::string;

namespace CGL {
class Model {
public:
    Model(const std::string& filepath, bool flipUV);

    void draw(CGL::Shader& Shader);
    void load(const std::string& filepath);

private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<CGL::TextureBase> loadTextures(aiMaterial* material, aiTextureType type, std::string typeName);

private:
    std::vector<CGL::Mesh> m_meshes;
    std::string m_directory;
    std::vector<CGL::TextureBase> textures_loaded;
    std::vector<CGL::TextureBase> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    bool m_flipUV = false;
};
}
