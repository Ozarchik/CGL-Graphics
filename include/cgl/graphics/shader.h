#ifndef CGL_SHADER_H
#define CGL_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <cgl/core/transform.h>

namespace cgl {

enum ShaderType {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER
};

enum ErrorCode {
    INVALID_ID
};

class Shader {

public:
    Shader() = default;
    Shader(const std::string& vShaderPath, const std::string& fShaderPath);
    Shader(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath);

    void setSourceCode(const std::string& vShaderCode, const std::string& fShaderCode, const std::string& gShaderCode = {});

    GLuint loadShader(const std::string& code, ShaderType type);
    std::string loadShaderFromFile(const std::string& path);

	void use();
    void done();

	GLuint id() const;

    void setModel(const cgl::Transform& model);
    void setView(const cgl::Transform& view);
    void setProjection(const cgl::Transform& projection);
    void setMVP(
        const cgl::Transform& model,
        const cgl::Transform& view,
        const cgl::Transform& projection
    );

    bool isValid() const;

    void setBool(const std::string& name, bool state);
    bool getBool(const std::string &name);

    void setTexture(const std::string &name, unsigned int id, int unit);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
    void setMat4(const std::string &name, const cgl::Transform& transform) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec2(const std::string& name, const glm::vec2& vec);
	void setVec3(const std::string& name, const glm::vec3& vec);
	void setVec3(const std::string& name, float x, float y, float z);

    GLint getUniformLoc(const std::string& name) const;

private:
    void compile(GLuint vId, GLuint fId);
    void compile(GLuint vId, GLuint fId, GLuint gId);

private:
    GLuint m_id = 0;
    bool m_isValid = false;
};
}

#endif
