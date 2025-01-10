#pragma once

#include <string>
#include <glad/glad.h>

namespace CGL {

enum ShaderType {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

class Shader {
public:
	Shader(const std::string& shaderSrc, ShaderType type);
	~Shader() = default;

	unsigned int id() const;

private:
	unsigned int m_id;
	const char* m_source = nullptr;	
};
};