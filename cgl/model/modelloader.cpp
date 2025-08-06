#include <cgl/model/modelloader.h>
#include <cgl/texture/textureloader.h>
#include <cgl/node.h>
#include <iostream>

CGL::Node* CGL::ModelLoader::load(const std::string& filepath, bool flipUV)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace;
    // unsigned int flags = aiProcess_Triangulate;
    // if (flipUV) flags |= aiProcess_FlipUVs;

    const aiScene* scene = importer.ReadFile(filepath, flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return {};
    }

    m_directory = filepath.substr(0, filepath.find_last_of('/'));

    std::vector<CGL::Mesh*> meshes;
    std::vector<CGL::Material> materials;
    processNode(scene, scene->mRootNode, meshes, materials);

    CGL::Transform modelTransform;
    // modelTransform.translateY(2.0f);
    CGL::Node* node = new CGL::Node(meshes, Shader::defaultModelShader(), modelTransform);
    return node;
}

void CGL::ModelLoader::processNode(const aiScene* scene, aiNode* node, std::vector<CGL::Mesh*>& meshes, std::vector<CGL::Material>& materials)
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

CGL::Mesh* CGL::ModelLoader::processMesh(const aiScene* scene, aiMesh* mesh)
{
    std::vector<CGL::Vertex> vertices = loadVertices(mesh);
    std::vector<unsigned int> indices  = loadIndices(mesh);

    return new CGL::Mesh(vertices, indices);
}

CGL::Material CGL::ModelLoader::processMaterial(const aiScene* scene, aiMesh* mesh)
{
    std::vector<CGL::TextureBase> textures = loadTextures(scene, mesh);

    return CGL::Material(textures);
}

std::vector<CGL::Vertex> CGL::ModelLoader::loadVertices(aiMesh* mesh)
{
    std::vector<CGL::Vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        CGL::Vertex vertex;
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
            vertex.texcoord.y = mesh->mTextureCoords[0][i].y;;
        } else {
            vertex.texcoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<CGL::TextureBase> CGL::ModelLoader::loadTextures(const aiScene *scene, aiMesh *mesh)
{
    std::vector<CGL::TextureBase> textures;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<CGL::TextureBase> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<CGL::TextureBase> specularMaps = loadTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return textures;
}

std::vector<unsigned int> CGL::ModelLoader::loadIndices(aiMesh *mesh)
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

std::vector<CGL::TextureBase> CGL::ModelLoader::loadTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<CGL::TextureBase> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

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
            CGL::TextureBase texture = CGL::TextureLoader::loadFromFile(m_directory + "/" + std::string(str.C_Str()));
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}
