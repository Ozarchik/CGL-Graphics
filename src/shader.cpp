#include "shader.h" 
#include <fstream>
#include <sstream>
#include <iostream>

CGL::Shader::Shader(const std::string& shaderSrc, ShaderType type)
{
	std::ifstream file;
	std::string code;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(shaderSrc.c_str());

		std::stringstream stream;
		stream << file.rdbuf();
		code = stream.str();

		file.close();
	} catch (std::ifstream::failure e) {
        std::cout << "Failed to load shader code from file: " << shaderSrc.c_str() << std::endl;
	}

	m_source = code.c_str();

	m_id = glCreateShader(type);
	glShaderSource(m_id, 1, &m_source, nullptr);
	glCompileShader(m_id);

	int sucess;
	char infoLog[512];

	glGetShaderiv(m_id, GL_COMPILE_STATUS, &sucess);
	if (!sucess) {
		glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "Vertex shader compile failed: " << infoLog << std::endl;
	} 
}

unsigned int CGL::Shader::id() const
{
	return m_id;
}
