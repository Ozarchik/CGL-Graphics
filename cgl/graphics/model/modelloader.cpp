#include <cgl/graphics/model/modelloader.h>
#include <cgl/graphics/texture/textureloader.h>
#include <cgl/graphics/scene/node.h>
#include <cgl/managers/resourcemanager.h>
#include <cgl/core/rendercontext.h>
#include <iostream>

std::shared_ptr<cgl::Node> cgl::ModelLoader::load(const std::string& filepath, bool flipUV)
{
    std::cout << "loading model from: " << filepath << std::endl;
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
    // unsigned int flags = aiProcess_Triangulate;
    // if (flipUV) flags |= aiProcess_FlipUVs;

    const aiScene* scene = importer.ReadFile(filepath, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    m_directory = filepath.substr(0, filepath.find_last_of('/'));

    std::vector<std::shared_ptr<cgl::Mesh>> meshes;
    std::vector<cgl::Material> materials;
    processNode(scene, scene->mRootNode, meshes, materials);

    // modelTransform.translateY(2.0f);
    auto node = std::make_shared<cgl::Node>(cgl::ResourceManager::loadDefaultModelShader());
    for (int i = 0; i < meshes.size(); i++) // not valid operation, need fix in future
    {
        node->addMesh(meshes[i], materials[i]);
    }
    return node;
}

void cgl::ModelLoader::processNode(const aiScene* scene, aiNode* node, std::vector<std::shared_ptr<cgl::Mesh>>& meshes, std::vector<cgl::Material>& materials)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(scene, mesh));
        materials.push_back(processMaterial(scene, mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(scene, node->mChildren[i], meshes, materials);
    }
}

std::shared_ptr<cgl::Mesh> cgl::ModelLoader::processMesh(const aiScene* scene, aiMesh* mesh)
{
    std::vector<cgl::Vertex> vertices = loadVertices(mesh);
    std::vector<unsigned int> indices  = loadIndices(mesh);

    return std::make_shared<cgl::Mesh>(vertices, indices);
}

cgl::Material cgl::ModelLoader::processMaterial(const aiScene* scene, aiMesh* mesh)
{
    std::vector<cgl::Texture> textures = loadTextures(scene, mesh);

    return cgl::Material(textures);
}

std::vector<cgl::Vertex> cgl::ModelLoader::loadVertices(aiMesh* mesh)
{
    std::vector<cgl::Vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        cgl::Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        if (mesh->HasNormals()) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0]) {
            vertex.texcoord.x = mesh->mTextureCoords[0][i].x;
            vertex.texcoord.y = mesh->mTextureCoords[0][i].y;
        } else {
            vertex.texcoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<cgl::Texture> cgl::ModelLoader::loadTextures(const aiScene *scene, aiMesh *mesh)
{
    std::vector<cgl::Texture> textures;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<cgl::Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, cgl::TextureType::Diffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<cgl::Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR, cgl::TextureType::Specular);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return textures;
}

std::vector<unsigned int> cgl::ModelLoader::loadIndices(aiMesh *mesh)
{
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return indices;
}

std::vector<cgl::Texture> cgl::ModelLoader::loadTextures(aiMaterial* mat, aiTextureType assimpType, cgl::TextureType cglType)
{
    std::vector<cgl::Texture> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(assimpType); i++)
    {
        aiString str;
        mat->GetTexture(assimpType, i, &str);

        bool skip = false;

        for(unsigned int j = 0; j < textures_loaded.size(); j++) {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if(!skip) {
            std::cout << "load from: " << m_directory + "/" + std::string(str.C_Str()) << std::endl;
            cgl::Texture texture = cgl::TextureLoader::loadFromFile(m_directory + "/" + std::string(str.C_Str()));
            texture.type = cglType;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}
