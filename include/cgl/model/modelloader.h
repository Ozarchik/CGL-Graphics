#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <string>

#include <cgl/shader.h>
#include <cgl/texture/texture.h>
#include <cgl/mesh/common/mesh.h>
#include <cgl/material.h>

namespace CGL {
class Node;
class ModelLoader {
public:
    ModelLoader() = default;
    CGL::Node* load(const std::string& filepath, bool flipUV = false);

private:
    void processNode(const aiScene* scene, aiNode* node, std::vector<CGL::Mesh*>& meshes, std::vector<CGL::Material>& materials);
    CGL::Mesh* processMesh(const aiScene* scene, aiMesh* mesh);
    CGL::Material processMaterial(const aiScene* scene, aiMesh* mesh);

    std::vector<CGL::Vertex> loadVertices(aiMesh *mesh);
    std::vector<unsigned int> loadIndices(aiMesh *mesh);
    std::vector<CGL::Texture> loadTextures(const aiScene* scene, aiMesh* mesh);
    std::vector<CGL::Texture> loadTextures(aiMaterial* material, aiTextureType type, std::string typeName);


private:
    std::string m_directory;
    std::vector<CGL::Texture> textures_loaded;
    std::vector<CGL::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
}
