#ifndef CGL_RESOURCEMANAGER_H
#define CGL_RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <mutex>
#include <cgl/graphics/shader.h>
#include <cgl/graphics/scene/node.h>

namespace CGL {
class ResourceManager
{
public:
    ResourceManager();
    static void init();

    static CGL::Texture loadTexture(const std::string& name);
    static std::shared_ptr<CGL::Shader> loadShader(const std::string &name);
    static std::shared_ptr<CGL::Node> loadModel(const std::string& name);

    static CGL::Shader& loadDefaultShader();
    static std::shared_ptr<Shader> loadDefaultModelShader();

    static void setTexturesDirectoryPath(const std::string& path);
    static void setModelsDirectoryPath(const std::string& path);
    static void setShadersDirectoryPath(const std::string& path);

private:
    inline static std::mutex m_mutex;
    inline static std::string m_texturesDirectory = "textures";
    inline static std::string m_modelsDirectory = "models";
    inline static std::string m_shadersDirectory = "shaders";

    inline static std::unordered_map<std::string, std::weak_ptr<Shader>> m_shaderCache;
};
}

#endif // RESOURCEMANAGER_H
