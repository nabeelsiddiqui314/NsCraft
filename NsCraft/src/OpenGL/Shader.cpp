#include "Shader.h"
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	loadShader(vertexPath, fragmentPath);
}

void Shader::loadShader(const char* vertexPath, const char* fragmentPath) {
	std::string	vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_READING_UNSUCCESSFUL" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

	glCompileShader(vertexShader);
	CheckCompileErrors(vertexShader, "VERTEX");
	glCompileShader(fragmentShader);
	CheckCompileErrors(fragmentShader, "FRAGMENT");

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	CheckCompileErrors(m_program, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::bind() {
	glUseProgram(m_program);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int val) {
	glUniform1i(getUniformLocation(name), val);
}

void Shader::setUniform1f(const std::string& name, float val) {
	glUniform1f(getUniformLocation(name), val);
}

void Shader::setUniform4f(const std::string& name, const glm::vec4& val) {
	glUniform4f(getUniformLocation(name), val.x, val.y, val.z, val.w);
}

GLint Shader::getUniformLocation(const std::string& name) {
	if (m_uniformCache.find(name) != m_uniformCache.end())
		return m_uniformCache.at(name);
	m_uniformCache.insert(std::make_pair(name, glGetUniformLocation(m_program, name.c_str())));
	return m_uniformCache.at(name);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& val) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &val[0][0]);
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& val) {
	glUniform3f(getUniformLocation(name), val.x, val.y, val.z);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}