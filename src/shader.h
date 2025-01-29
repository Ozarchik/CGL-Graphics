#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "transform.h"

namespace CGL {

enum ShaderType {
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

enum ErrorCode {
    INVALID_ID
};

class Shader {

public:
    Shader() = default;
    Shader(const std::string& vShaderPath, const std::string& fShaderPath);

    GLuint loadShader(const std::string& shaderSrc, ShaderType type);

	void use();

	GLuint id() const;

	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
    void setMat4(const std::string &name, const CGL::Transform& transform) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setVec3(const std::string& name, const glm::vec3& vec);
	void setVec3(const std::string& name, float x, float y, float z);

	GLint getUniformLoc(const std::string& name) const;

private:
    void compile(GLuint vId, GLuint fId);

private:
    GLuint m_id;
};
};
