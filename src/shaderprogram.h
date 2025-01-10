#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

namespace CGL {
class ShaderProgram {

public:
	ShaderProgram() = default;
	ShaderProgram(CGL::Shader& vShader, CGL::Shader& fShader);
	ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath);
	void use();

	GLuint id() const;

	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setVec3(const std::string& name, const glm::vec3& vec);
	void setVec3(const std::string& name, float x, float y, float z);

	GLint getUniformLoc(const std::string& name) const;

private:
	void create(CGL::Shader& vShader, CGL::Shader& fShader);

private:
	GLuint m_id;
};
};