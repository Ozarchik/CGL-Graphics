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
    m_texturesDirectory = (std::filesystem::current_path() / "textures").string();
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

CGL::Shader& CGL::ResourceManager::loadDefaultShader()
{
    static CGL::Shader shader;
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

CGL::Shader& CGL::ResourceManager::loadDefaultModelShader()
{
    static CGL::Shader shader = ResourceManager::loadShader("model");
    return shader;
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
