#include <cgl/shader.h>
#include <iostream>
#include <fstream>
#include <sstream>
// #include <filesystem>

#define SHADER_LOG_MODE false

CGL::Shader::Shader(const std::string& vShaderPath, const std::string& fShaderPath)
{
    GLuint vId = loadShader(vShaderPath, CGL::VERTEX_SHADER);
    GLuint fId = loadShader(fShaderPath, CGL::FRAGMENT_SHADER);
    compile(vId, fId);
}

CGL::Shader::Shader(const std::string &vShaderPath, const std::string &fShaderPath, const std::string &gShaderPath)
{
    GLuint vId = loadShader(vShaderPath, CGL::VERTEX_SHADER);
    GLuint fId = loadShader(fShaderPath, CGL::FRAGMENT_SHADER);
    GLuint gId = loadShader(gShaderPath, CGL::GEOMETRY_SHADER);
    compile(vId, fId, gId);
}


GLuint CGL::Shader::loadShader(const std::string& shaderSrc, ShaderType type)
{
    std::ifstream file;
    std::string code;
    GLuint shaderId;

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


    shaderId = glCreateShader(type);
    auto srcCode = code.c_str();
    glShaderSource(shaderId, 1, &srcCode, nullptr);
    glCompileShader(shaderId);

    int sucess;
    char infoLog[512];

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        if (type == VERTEX_SHADER) {
            std::cout << "Vertex shader compile failed: " << infoLog << std::endl;
        } else if (type == FRAGMENT_SHADER) {
            std::cout << "Fragment shader compile failed: " << infoLog << std::endl;
        } else if (type == GEOMETRY_SHADER) {
            std::cout << "Geometry shader compile failed: " << infoLog << std::endl;
        } else {
            std::cout << "Underfined shader compile failed: " << infoLog << std::endl;
        }
        return INVALID_ID;
    }

    return shaderId;
}

void CGL::Shader::use()
{
	glUseProgram(m_id);
}

GLuint CGL::Shader::id() const
{
	return m_id;
}

void CGL::Shader::setMVP(
    const CGL::Transform& model,
    const CGL::Transform& view,
    const CGL::Transform& projection
)
{
    setMat4("model", model.data());
    setMat4("view", view.data());
    setMat4("projection", projection.data());
}

void CGL::Shader::setBool(const std::string& name, bool state)
{
    glUniform1i(getUniformLoc(name), state);
}

bool CGL::Shader::getBool(const std::string& name)
{
    int state[1];
    glGetUniformiv(m_id, getUniformLoc(name), state);

    return state[0];
}

void CGL::Shader::setInt(const std::string& name, int value)
{
	glUniform1i(getUniformLoc(name), value);
}

void CGL::Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(getUniformLoc(name), value);
}

void CGL::Shader::setMat4(const std::string &name, const CGL::Transform& transform) const
{
    setMat4(name, transform.data());
}

void CGL::Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLint CGL::Shader::getUniformLoc(const std::string& name) const
{
    GLint loc = glGetUniformLocation(m_id, name.c_str());

    if (SHADER_LOG_MODE && loc == -1) {
        std::cout << "Uniform [" << name  << "] is not found" << std::endl;
    }

    return loc;
}

CGL::Shader &CGL::Shader::defaultModelShader()
{
    static CGL::Shader shader("shaders/model.vert", "shaders/model.frag");
    return shader;
}

void CGL::Shader::compile(GLuint vId, GLuint fId)
{
    m_id = glCreateProgram();
    glAttachShader(m_id, vId);
    glAttachShader(m_id, fId);
    glLinkProgram(m_id);

    int sucess;
    char infoLog[512];

    glGetProgramiv(m_id, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "Shader program link failed: " << infoLog << std::endl;
    }
}

void CGL::Shader::compile(GLuint vId, GLuint fId, GLuint gId)
{
    m_id = glCreateProgram();
    glAttachShader(m_id, vId);
    glAttachShader(m_id, fId);
    glAttachShader(m_id, gId);
    glLinkProgram(m_id);

    int sucess;
    char infoLog[512];

    glGetProgramiv(m_id, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
        std::cout << "Shader program link failed: " << infoLog << std::endl;
    }
}

void CGL::Shader::setVec2(const std::string &name, const glm::vec2 &vec)
{
    glUniform2f(getUniformLoc(name), vec.x, vec.y);
}

void CGL::Shader::setVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(getUniformLoc(name), x, y, z);
}

void CGL::Shader::setVec3(const std::string& name, const glm::vec3& vec)
{
	glUniform3f(getUniformLoc(name), vec.x, vec.y, vec.z);
}
