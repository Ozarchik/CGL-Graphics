#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <string>

#include <cgl/shader.h>
#include <cgl/texture/texturebase.h>
#include <cgl/mesh/common/mesh.h>
#include <cgl/model/model.h>

namespace CGL {
class ModelLoader {
public:
    ModelLoader() = default;
    CGL::Model load(const std::string& filepath, bool flipUV = false);

private:
    void processNode(const aiScene* scene, aiNode* node, std::vector<CGL::Mesh>& meshes);
    Mesh processMesh(const aiScene* scene, aiMesh* mesh);

    std::vector<CGL::Vertex> loadVertices(aiMesh *mesh);
    std::vector<unsigned int> loadIndices(aiMesh *mesh);
    std::vector<CGL::TextureBase> loadTextures(const aiScene* scene, aiMesh* mesh);
    std::vector<CGL::TextureBase> loadTextures(aiMaterial* material, aiTextureType type, std::string typeName);


private:
    std::string m_directory;
    std::vector<CGL::TextureBase> textures_loaded;
    std::vector<CGL::TextureBase> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
}
