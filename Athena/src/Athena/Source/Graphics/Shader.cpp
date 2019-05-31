#include "ath_pch.h"

#include "Graphics/Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void GLClearError();

bool GLLogCall(const char * function, const char * file, int line);

#define LOG(x) std::cout << x << std::endl

#define ASSERT(x) if (!(x)) __debugbreak()

#define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char * function, const char * file, int line) {
	while (GLenum error = glGetError()) {
		LOG("[OpenGL] (" << std::hex << error << ") : " << function << " " << file << " : " << std::dec << line << std::endl);
		return false;
	}
	return true;
}

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0) {
	ShaderProgramSource source = ParseShader(filepath);

	showShaderSource(source);

	m_RendererID = createShader(source.VertexSource, source.ShaderSource);
	Bind();
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}


void Shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unBind() const {
	GLCall(glUseProgram(0));
}

// set Uniforms
void Shader::SetUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}


void Shader::SetUniform3f(const std::string& name, glm::vec3 vector) {
	this->SetUniform3f(name, vector.x, vector.y, vector.z);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 vector) {
	this->SetUniform4f(name, vector.x, vector.y, vector.z, vector.w);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const float * data) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, data));
}

int Shader::GetUniformLocation(const std::string& name) {

	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
		CORE_WARN("Warning: uniform : " + name + " does not exist");

	m_UniformLocationCache[name] = location;

	return location;
}

void Shader::showShaderSource(const ShaderProgramSource & source) {
	LOG("VERTEX");
	CORE_INFO(source.VertexSource.c_str());
	LOG("FRAGMENT");
	CORE_INFO(source.ShaderSource);
}


int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int result;
	glGetShaderiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
		char * message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(program, length, &length, message);
		std::cout << "WARN ( potential error ) :: Failed to link: " << std::endl;
		std::cout << std::dec << message << std::endl;
	}

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::CompileShader(const std::string& source, unsigned int type) {
	unsigned int id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}


Shader::ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		} else
			ss[(int)type] << line << '\n';
	}

	return { ss[0].str(), ss[1].str() };
}