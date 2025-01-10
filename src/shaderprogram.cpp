#include "shaderprogram.h"
#include <iostream>

CGL::ShaderProgram::ShaderProgram(CGL::Shader& vShader, CGL::Shader& fShader)
{
	create(vShader, fShader);
}

CGL::ShaderProgram::ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath)
{
	CGL::Shader vShader(vShaderPath, CGL::VERTEX_SHADER);
    CGL::Shader fShader(fShaderPath, CGL::FRAGMENT_SHADER);
    create(vShader, fShader);
}

void CGL::ShaderProgram::create(CGL::Shader& vShader, CGL::Shader& fShader)
{
	m_id = glCreateProgram();
	glAttachShader(m_id, vShader.id());
	glAttachShader(m_id, fShader.id());
	glLinkProgram(m_id);

	int sucess;
	char infoLog[512];

	glGetProgramiv(m_id, GL_LINK_STATUS, &sucess);
	if (!sucess) {
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "Shader program link failed: " << infoLog << std::endl;
	}
}


void CGL::ShaderProgram::use()
{
	glUseProgram(m_id);
}

GLuint CGL::ShaderProgram::id() const
{
	return m_id;
}

void CGL::ShaderProgram::setInt(const std::string& name, int value)
{
	glUniform1i(getUniformLoc(name), value);
}

void CGL::ShaderProgram::setFloat(const std::string& name, float value)
{
	glUniform1f(getUniformLoc(name), value);
}

void CGL::ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLint CGL::ShaderProgram::getUniformLoc(const std::string& name) const
{
	return glGetUniformLocation(m_id, name.c_str());
}

void CGL::ShaderProgram::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(getUniformLoc(name), x, y, z);
}

void CGL::ShaderProgram::setVec3(const std::string& name, const glm::vec3& vec)
{
	glUniform3f(getUniformLoc(name), vec.x, vec.y, vec.z);
}