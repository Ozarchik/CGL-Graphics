#ifndef CGL_RESOURCEMANAGER_H
#define CGL_RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <cgl/graphics/shader.h>
#include <cgl/graphics/scene/node.h>

namespace CGL {
class ResourceManager
{
public:
    ResourceManager();
    static void init();

    static CGL::Texture loadTexture(const std::string& name);
    static CGL::Shader loadShader(const std::string& name);
    static std::shared_ptr<CGL::Node> loadModel(const std::string& name);

    static CGL::Shader& loadDefaultShader();
    static CGL::Shader& loadDefaultModelShader();

    static void setTexturesDirectoryPath(const std::string& path);
    static void setModelsDirectoryPath(const std::string& path);
    static void setShadersDirectoryPath(const std::string& path);

private:
    inline static std::string m_texturesDirectory = "textures";
    inline static std::string m_modelsDirectory = "models";
    inline static std::string m_shadersDirectory = "shaders";
};
}

#endif // RESOURCEMANAGER_H
