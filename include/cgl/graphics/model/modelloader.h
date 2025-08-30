#ifndef CGL_MODELLOADER_H
#define CGL_MODELLOADER_H

#include <glad/glad.h>
#include <string>
#include <memory>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <cgl/graphics/shader.h>
#include <cgl/graphics/texture/texture.h>
#include <cgl/graphics/mesh/common/mesh.h>
#include <cgl/graphics/material/material.h>

namespace cgl {
class Node;
class ModelLoader {
public:
    ModelLoader() = default;
    std::shared_ptr<cgl::Node> load(const std::string& filepath, bool flipUV = false);

private:
    void processNode(const aiScene* scene, aiNode* node, std::vector<std::shared_ptr<Mesh> > &meshes, std::vector<cgl::Material>& materials);
    std::shared_ptr<Mesh> processMesh(const aiScene* scene, aiMesh* mesh);
    cgl::Material processMaterial(const aiScene* scene, aiMesh* mesh);

    std::vector<cgl::Vertex> loadVertices(aiMesh *mesh);
    std::vector<unsigned int> loadIndices(aiMesh *mesh);
    std::vector<cgl::Texture> loadTextures(const aiScene* scene, aiMesh* mesh);
    std::vector<cgl::Texture> loadTextures(aiMaterial* material, aiTextureType assimpType, TextureType cglType);


private:
    std::string m_directory;
    std::vector<cgl::Texture> textures_loaded;
    std::vector<cgl::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
}

#endif
