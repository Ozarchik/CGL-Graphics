#include <cgl/managers/resourcemanager.h>
#include <cgl/graphics/model/modelloader.h>
#include <cgl/graphics/texture/textureloader.h>
#include <filesystem>

cgl::ResourceManager::ResourceManager()
{
}

void cgl::ResourceManager::init()
{
    m_modelsDirectory = (std::filesystem::current_path() / "assets/models").string();
    m_shadersDirectory = (std::filesystem::current_path() / "shaders").string();
    m_texturesDirectory = (std::filesystem::current_path() / "textures").string();
}

cgl::Texture cgl::ResourceManager::loadTexture(const std::string &name)
{
    return cgl::TextureLoader::loadFromFile(m_texturesDirectory + "/" + name);
}

std::shared_ptr<cgl::Shader> cgl::ResourceManager::loadShader(const std::string &name)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    auto it = m_shaderCache.find(name);
    if (it != m_shaderCache.end() && !it->second.expired()) {
        return it->second.lock();
    }

    std::shared_ptr<Shader> shader = std::make_shared<cgl::Shader>(
        m_shadersDirectory + "/" + name + ".vert",
        m_shadersDirectory + "/" + name + ".frag"
    );

    m_shaderCache[name] = shader;
    return shader;
}

cgl::Shader& cgl::ResourceManager::loadDefaultShader()
{
    static cgl::Shader shader;
    shader.setSourceCode(
        std::string(
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aNormal;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "layout (location = 3) in vec3 aColor;\n"

            "out vec3 fPos;\n"
            "out vec3 fNormal;\n"
            "out vec2 fTexCoord;\n"
            "out vec3 fColor;\n"

            "uniform mat4 model;\n"
            "uniform mat4 view;\n"
            "uniform mat4 projection;\n"

            "void main() {\n"
            "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
            "    fColor = aColor;\n"
            "    fNormal = aNormal;\n"
            "    fTexCoord = aTexCoord;\n"
            "}\n"
    ),
        std::string(
            "#version 330 core\n"

            "in vec3 fPos;\n"
            "in vec3 fNormal;\n"
            "in vec2 fTexCoord;\n"
            "in vec3 fColor;\n"

            "uniform bool useTexture;\n"
            "uniform bool selected;\n"
            "uniform sampler2D texture_diffuse1;\n"

            "out vec4 FragColor;\n"
            "void main() {\n"
            "    if (useTexture)\n"
            "        FragColor = texture(texture_diffuse1, fTexCoord);\n"
            "    else\n"
            "        FragColor = vec4(fColor, 1.0);\n"
            "   if (selected)\n"
            "        FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"
            "}\n"
        )
    );

    return shader;
}

std::shared_ptr<cgl::Shader> cgl::ResourceManager::loadDefaultModelShader()
{
    static auto shader = ResourceManager::loadShader("model");
    return shader;
}

std::shared_ptr<cgl::Node> cgl::ResourceManager::loadModel(const std::string &name)
{
    cgl::ModelLoader loader;
    return loader.load(m_modelsDirectory + "/" + name);
}

void cgl::ResourceManager::setTexturesDirectoryPath(const std::string &path)
{
    m_texturesDirectory = path;
}

void cgl::ResourceManager::setShadersDirectoryPath(const std::string &path)
{
    m_shadersDirectory = path;
}

std::string cgl::ResourceManager::getShaderPath()
{
    return m_shadersDirectory;
}

std::string cgl::ResourceManager::getModelPath()
{
    return m_modelsDirectory;
}

std::string cgl::ResourceManager::getTexturePath()
{
    return m_texturesDirectory;
}

void cgl::ResourceManager::setModelsDirectoryPath(const std::string &path)
{
    m_modelsDirectory = path;
}
