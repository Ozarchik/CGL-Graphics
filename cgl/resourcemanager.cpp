#include <cgl/resourcemanager.h>
#include <cgl/model/modelloader.h>
#include <cgl/texture/textureloader.h>
#include <filesystem>

CGL::ResourceManager::ResourceManager()
{
}

void CGL::ResourceManager::init()
{
    m_modelsDirectory = (std::filesystem::current_path() / "assets/models").string();
    m_shadersDirectory = (std::filesystem::current_path() / "shaders").string();
    m_texturesDirectory = (std::filesystem::current_path() / "textrues").string();
}

CGL::Texture CGL::ResourceManager::loadTexture(const std::string &name)
{
    return CGL::TextureLoader::loadFromFile(m_texturesDirectory + "/" + name);
}

CGL::Shader CGL::ResourceManager::loadShader(const std::string &name)
{
    return CGL::Shader(
        m_shadersDirectory + "/" + name + ".vert",
        m_shadersDirectory + "/" + name + ".frag"
    );
}

CGL::Node* CGL::ResourceManager::loadModel(const std::string &name)
{
    CGL::ModelLoader loader;
    return loader.load(m_modelsDirectory + "/" + name);
}

void CGL::ResourceManager::setTexturesDirectoryPath(const std::string &path)
{
    m_texturesDirectory = path;
}

void CGL::ResourceManager::setShadersDirectoryPath(const std::string &path)
{
    m_shadersDirectory = path;
}

void CGL::ResourceManager::setModelsDirectoryPath(const std::string &path)
{
    m_modelsDirectory = path;
}
