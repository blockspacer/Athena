#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class ATHENA_API Shader {

	struct ShaderProgramSource {
		std::string VertexSource;
		std::string ShaderSource;
	};

private:
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	unsigned int m_RendererID;

	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void unBind() const;

	// set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform3f(const std::string& name, glm::vec3 vector);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, glm::vec4 vector);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4fv(const std::string& name, const float * data);

	int GetUniformLocation(const std::string& name);

private:

	int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	ShaderProgramSource ParseShader(const std::string& filepath);

	int CompileShader(const std::string& source, unsigned int type);

	void showShaderSource(const ShaderProgramSource & source);

};